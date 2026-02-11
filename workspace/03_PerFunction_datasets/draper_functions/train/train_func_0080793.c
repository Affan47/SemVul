ZIPDecode(TIFF* tif, uint8* op, tmsize_t occ, uint16 s)
{
  static const char module[] = "ZIPDecode";
  ZIPState* sp = DecoderState(tif);

  (void) s;
  assert(sp != NULL);
  assert(sp->state == ZSTATE_INIT_DECODE);

        sp->stream.next_in = tif->tif_rawcp;
  sp->stream.avail_in = (uInt) tif->tif_rawcc;

  sp->stream.next_out = op;
  assert(sizeof(sp->stream.avail_out)==4);


  sp->stream.avail_out = (uInt) occ;
  if ((tmsize_t)sp->stream.avail_out != occ)
  {
    TIFFErrorExt(tif->tif_clientdata, module, "ZLib cannot deal with buffers this size");
    return (0);
  }
  do {
    int state = inflate(&sp->stream, Z_PARTIAL_FLUSH);
    if (state == Z_STREAM_END)
      break;
    if (state == Z_DATA_ERROR) {
      TIFFErrorExt(tif->tif_clientdata, module,
          "Decoding error at scanline %lu, %s",
          (unsigned long) tif->tif_row, sp->stream.msg);
      if (inflateSync(&sp->stream) != Z_OK)
        return (0);
      continue;
    }
    if (state != Z_OK) {
      TIFFErrorExt(tif->tif_clientdata, module, "ZLib error: %s",
          sp->stream.msg);
      return (0);
    }
  } while (sp->stream.avail_out > 0);
  if (sp->stream.avail_out != 0) {
    TIFFErrorExt(tif->tif_clientdata, module,
        "Not enough data at scanline %lu (short " TIFF_UINT64_FORMAT " bytes)",
        (unsigned long) tif->tif_row, (TIFF_UINT64_T) sp->stream.avail_out);
    return (0);
  }

        tif->tif_rawcp = sp->stream.next_in;
        tif->tif_rawcc = sp->stream.avail_in;

  return (1);
}
