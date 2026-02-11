parse_n_tri_object (vtk3DSImporter *importer, vtk3DSChunk *mainchunk)
{
  vtk3DSMesh *mesh;
  vtk3DSChunk chunk;

  mesh = create_mesh (obj_name, 0, 0);

  do
    {
    start_chunk (importer, &chunk);

    if (chunk.end <= mainchunk->end)
      {
      switch (chunk.tag)
        {
        case 0x4110: parse_point_array(importer, mesh);
          break;
        case 0x4120: parse_face_array (importer, mesh, &chunk);
          break;
        case 0x4160: parse_mesh_matrix(importer, mesh);
          break;
        }
      }

    end_chunk (importer, &chunk);
    } while (chunk.end <= mainchunk->end);

  VTK_LIST_INSERT (importer->MeshList, mesh);
}
