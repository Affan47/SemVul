file_bounding_box_of_nodes_impl(Lib3dsNode *node, Lib3dsFile *file,
                                int include_meshes, int include_cameras, int include_lights,
                                float bmin[3], float bmax[3], float matrix[4][4]) {
    switch (node->type) {
        case LIB3DS_NODE_MESH_INSTANCE:
            if (include_meshes) {
                int index;
                Lib3dsMeshInstanceNode *n = (Lib3dsMeshInstanceNode*)node;

                index = lib3ds_file_mesh_by_name(file, n->instance_name);
                if (index < 0)
                    index = lib3ds_file_mesh_by_name(file, node->name);
                if (index >= 0) {
                    Lib3dsMesh *mesh;
                    float inv_matrix[4][4], M[4][4];
                    float v[3];
                    int i;

                    mesh = file->meshes[index];
                    lib3ds_matrix_copy(inv_matrix, mesh->matrix);
                    lib3ds_matrix_inv(inv_matrix);
                    lib3ds_matrix_mult(M, matrix, node->matrix);
                    lib3ds_matrix_translate(M, -n->pivot[0], -n->pivot[1], -n->pivot[2]);
                    lib3ds_matrix_mult(M, M, inv_matrix);

                    for (i = 0; i < mesh->nvertices; ++i) {
                        lib3ds_vector_transform(v, M, mesh->vertices[i]);
                        lib3ds_vector_min(bmin, v);
                        lib3ds_vector_max(bmax, v);
                    }
                }
            }
            break;

        case LIB3DS_NODE_CAMERA:
        case LIB3DS_NODE_CAMERA_TARGET:
            if (include_cameras) {
                float z[3], v[3];
                float M[4][4];
                lib3ds_matrix_mult(M, matrix, node->matrix);
                lib3ds_vector_zero(z);
                lib3ds_vector_transform(v, M, z);
                lib3ds_vector_min(bmin, v);
                lib3ds_vector_max(bmax, v);
            }
            break;

        case LIB3DS_NODE_OMNILIGHT:
        case LIB3DS_NODE_SPOTLIGHT:
        case LIB3DS_NODE_SPOTLIGHT_TARGET:
            if (include_lights) {
                float z[3], v[3];
                float M[4][4];
                lib3ds_matrix_mult(M, matrix, node->matrix);
                lib3ds_vector_zero(z);
                lib3ds_vector_transform(v, M, z);
                lib3ds_vector_min(bmin, v);
                lib3ds_vector_max(bmax, v);
            }
            break;
    }
    {
        Lib3dsNode *p = node->childs;
        while (p) {
            file_bounding_box_of_nodes_impl(p, file, include_meshes, include_cameras, include_lights, bmin, bmax, matrix);
            p = p->next;
        }
    }
}
