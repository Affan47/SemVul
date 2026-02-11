he_rewind_command(struct he_s *hedit)


{
  long position;
  char bigendian[4];

  fseek(hedit->undo.swapfile, -4, SEEK_CUR);
  if (fread(bigendian, 4, 1, hedit->undo.swapfile) < 1)
    return -1;
  position = he_bigendian_to_long(bigendian);
  if (!position) return -1;
  fseek(hedit->undo.swapfile, position, SEEK_SET);
  return position;
}
