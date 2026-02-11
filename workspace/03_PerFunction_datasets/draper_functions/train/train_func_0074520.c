flag_array_write(Lib3dsMesh *mesh, Lib3dsIo *io)
{
  Lib3dsChunk c;
  unsigned i;

  if (!mesh->flags || !mesh->flagL) {
    return(LIB3DS_TRUE);
  }
  ASSERT(mesh->flags<0x10000);
  c.chunk=LIB3DS_POINT_FLAG_ARRAY;
  c.size=8+2*mesh->flags;
  lib3ds_chunk_write(&c, io);

  lib3ds_io_write_word(io, (Lib3dsWord)mesh->flags);
  for (i=0; i<mesh->flags; ++i) {
    lib3ds_io_write_word(io, mesh->flagL[i]);
  }
  return(LIB3DS_TRUE);
}
