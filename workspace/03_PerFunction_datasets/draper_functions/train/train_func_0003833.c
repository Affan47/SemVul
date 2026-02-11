read_memstate(dest_t *dest, glui32 chunklen)
{
  glui32 chunkend = dest->pos + chunklen;
  glui32 newlen;
  glui32 res, pos;
  int val;
  int runlen;
  unsigned char ch, ch2;

  heap_clear();

  res = read_long(dest, &newlen);
  if (res)
    return res;

  res = change_memsize(newlen, FALSE);
  if (res)
    return res;

  runlen = 0;
  glk_stream_set_position(gamefile, gamefile_start+ramstart, seekmode_Start);

  for (pos=ramstart; pos<endmem; pos++) {
    if (pos < endgamefile) {
      val = glk_get_char_stream(gamefile);
      if (val == -1) {
        fatal_error("The game file ended unexpectedly while restoring.");
      }
      ch = (unsigned char)val;
    }
    else {
      ch = 0;
    }

    if (dest->pos >= chunkend) {

    }
    else if (runlen) {
      runlen--;
    }
    else {
      res = read_byte(dest, &ch2);
      if (res)
        return res;
      if (ch2 == 0) {
        res = read_byte(dest, &ch2);
        if (res)
          return res;
        runlen = (glui32)ch2;
      }
      else {
        ch ^= ch2;
      }
    }

    if (pos >= protectstart && pos < protectend)
      continue;

    MemW1(pos, ch);
  }

  return 0;
}
