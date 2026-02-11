lib3ds_bool_track_write(Lib3dsBoolTrack *track, Lib3dsIo *io)
{
  Lib3dsBoolKey *k;
  Lib3dsDword num=0;
  for (k=track->keyL; k; k=k->next) {
    ++num;
  }
  lib3ds_io_write_word(io, (Lib3dsWord)track->flags);
  lib3ds_io_write_dword(io, 0);
  lib3ds_io_write_dword(io, 0);
  lib3ds_io_write_dword(io, num);

  for (k=track->keyL; k; k=k->next) {
    if (!lib3ds_tcb_write(&k->tcb,io)) {
      return(LIB3DS_FALSE);
    }
  }
  return(LIB3DS_TRUE);
}
