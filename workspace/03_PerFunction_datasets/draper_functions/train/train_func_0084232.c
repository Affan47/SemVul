file_seek(jas_stream_obj_t *obj, long offset, int origin)
{
  imBinFile* file_bin = (imBinFile*)obj;
  switch (origin)
  {
  case SEEK_SET:
    imBinFileSeekTo(file_bin, offset);
    break;
  case SEEK_CUR:
    imBinFileSeekOffset(file_bin, offset);
    break;
  case SEEK_END:
    imBinFileSeekFrom(file_bin, offset);
    break;
  }

  return imBinFileError(file_bin);
}
