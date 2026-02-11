XUtf8LookupString(XIC                 ic,
		  XKeyPressedEvent*   event,
		  char*               buffer_return,
		  int                 bytes_buffer,
		  KeySym*             keysym,
		  Status*             status_return) {

  long ucs = -1;
  int len;
  len = XmbLookupString(ic, event, buffer_return, bytes_buffer / 5,
		        keysym, status_return);
  if (*status_return == XBufferOverflow) {
    return len * 5;
  }
  if (*keysym > 0 && *keysym < 0x100 && len == 1) {
    if (*keysym < 0x80) {
      ucs = (unsigned char)buffer_return[0];
    } else {
      ucs = (long)*keysym;
    }
  } else  if (((*keysym >= 0x100 && *keysym <= 0xf000) ||
	      (*keysym & 0xff000000U) == 0x01000000))
  {
    ucs = XKeysymToUcs(*keysym);
  } else {
    ucs = -2;
  }

  if (ucs > 0) {
    len = XConvertUcsToUtf8((unsigned)ucs, (char *)buffer_return);
  } else if (len > 0) {
    XIM im;
    if (!ic) return 0;
    im = XIMOfIC(ic);
    if (!im) return 0;
    len = XConvertEucToUtf8(XLocaleOfIM(im), buffer_return, len, bytes_buffer);
  }
  return len;
}
