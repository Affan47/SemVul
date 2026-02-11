output_emf(ostream& out, short indent_size, short indent_level)
{
  LibFront::output_vector(out, indent_size, indent_level, EMF_VERTICES, NULL, nofVertices, vertexTags, false);

  if ( data.useFixedMeshN ) {
    LibFront::output_scalar(out, indent_size, indent_level, EMF_USE_MESH_N, NULL, 1);
  }

  return out;
}
