git_binary_search(glui32 key, glui32 keysize,
  glui32 start, glui32 structsize, glui32 numstructs,
  glui32 keyoffset, glui32 options)
{
  unsigned char keybuf[4];
  unsigned char byte, byte2;
  glui32 top, bot, val, addr;
  int ix;
  int retindex = ((options & serop_ReturnIndex) != 0);

  fetchkey(keybuf, key, keysize, options);

  bot = 0;
  top = numstructs;
  while (bot < top) {
    int cmp = 0;
    val = (top+bot) / 2;
    addr = start + val * structsize;

    if (keysize <= 4) {
      for (ix=0; (!cmp) && ix<keysize; ix++) {
	byte = memRead8(addr + keyoffset + ix);
	byte2 = keybuf[ix];
	if (byte < byte2)
	  cmp = -1;
	else if (byte > byte2)
	  cmp = 1;
      }
    }
    else {
      for (ix=0; (!cmp) && ix<keysize; ix++) {
	byte = memRead8(addr + keyoffset + ix);
	byte2 = memRead8(key + ix);
	if (byte < byte2)
	  cmp = -1;
	else if (byte > byte2)
	  cmp = 1;
      }
    }

    if (!cmp) {
      if (retindex)
	return val;
      else
	return addr;
    }

    if (cmp < 0) {
      bot = val+1;
    }
    else {
      top = val;
    }
  }

  if (retindex)
    return -1;
  else
    return 0;
}
