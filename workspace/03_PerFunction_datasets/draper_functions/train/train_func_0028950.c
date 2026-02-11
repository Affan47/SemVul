ascii_w_byte (Wire *w, void *v)
{
  SANE_Byte *b = v;

  switch (w->direction)
    {
    case WIRE_ENCODE:
      sanei_w_space (w, 3);
      *w->buffer.curr++ = hexdigit[(*b >> 4) & 0x0f];
      *w->buffer.curr++ = hexdigit[(*b >> 0) & 0x0f];
      *w->buffer.curr++ = '\n';
      break;

    case WIRE_DECODE:
      skip_ws (w);
      *b = get_byte (w);
      break;

    case WIRE_FREE:
      break;
    }
}
