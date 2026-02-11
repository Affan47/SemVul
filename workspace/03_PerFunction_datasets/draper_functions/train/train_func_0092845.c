lib3ds_file_bounding_box_of_objects(Lib3dsFile *file, int
                                    include_meshes, int include_cameras, int include_lights,
                                    float bmin[3], float bmax[3]) {
    bmin[0] = bmin[1] = bmin[2] = FLT_MAX;
    bmax[0] = bmax[1] = bmax[2] = -FLT_MAX;

    if (include_meshes) {
        float lmin[3], lmax[3];
        int i;
        for (i = 0; i < file->nmeshes; ++i) {
            lib3ds_mesh_bounding_box(file->meshes[i], lmin, lmax);
            lib3ds_vector_min(bmin, lmin);
            lib3ds_vector_max(bmax, lmax);
        }
    }
    if (include_cameras) {
        int i;
        for (i = 0; i < file->ncameras; ++i) {
            lib3ds_vector_min(bmin, file->cameras[i]->position);
            lib3ds_vector_max(bmax, file->cameras[i]->position);
            lib3ds_vector_min(bmin, file->cameras[i]->target);
            lib3ds_vector_max(bmax, file->cameras[i]->target);
        }
    }
    if (include_lights) {
        int i;
        for (i = 0; i < file->ncameras; ++i) {
            lib3ds_vector_min(bmin, file->lights[i]->position);
            lib3ds_vector_max(bmax, file->lights[i]->position);
            if (file->lights[i]->spot_light) {
                lib3ds_vector_min(bmin, file->lights[i]->target);
                lib3ds_vector_max(bmax, file->lights[i]->target);
            }
        }
    }
}
