lib3ds_mesh_new_face_list(Lib3dsMesh *mesh, Lib3dsDword faces)
{
  ASSERT(mesh);
  if (mesh->faceL) {
    ASSERT(mesh->faces);
    lib3ds_mesh_free_face_list(mesh);
  }
  ASSERT(!mesh->faceL && !mesh->faces);
  mesh->faces=0;
  mesh->faceL=calloc(sizeof(Lib3dsFace)*faces,1);
  if (!mesh->faceL) {
    LIB3DS_ERROR_LOG;
    return(LIB3DS_FALSE);
  }
  mesh->faces=faces;
  return(LIB3DS_TRUE);
}
