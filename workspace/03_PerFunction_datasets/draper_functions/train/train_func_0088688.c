lookChar() {
  Guchar in[16];
  int c, i;

  c = EOF;
  switch (algo) {
  case cryptRC4:
    if (state.rc4.buf == EOF) {
      c = str->getChar();
      if (c != EOF) {
	state.rc4.buf = rc4DecryptByte(state.rc4.state, &state.rc4.x,
				       &state.rc4.y, (Guchar)c);
      }
    }
    c = state.rc4.buf;
    break;
  case cryptAES:
    if (state.aes.bufIdx == 16) {
      for (i = 0; i < 16; ++i) {
	if ((c = str->getChar()) == EOF) {
	  return EOF;
	}
	in[i] = c;
      }
      aesDecryptBlock(&state.aes, in, str->lookChar() == EOF);
    }
    if (state.aes.bufIdx == 16) {
      c = EOF;
    } else {
      c = state.aes.buf[state.aes.bufIdx];
    }
    break;
  }
  return c;
}
