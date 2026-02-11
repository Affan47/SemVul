parse_MThd (GstMidiParse * midiparse, guint8 * data, guint size)
{
  guint16 format, ntracks, division;
  gboolean multitrack;

  format = GST_READ_UINT16_BE (data);
  switch (format) {
    case 0:
      multitrack = FALSE;
      break;
    case 1:
      multitrack = TRUE;
      break;
    default:
    case 2:
      goto invalid_format;
  }
  ntracks = GST_READ_UINT16_BE (data + 2);
  if (ntracks > 1 && !multitrack)
    goto invalid_tracks;

  division = GST_READ_UINT16_BE (data + 4);
  if (division & 0x8000)
    goto invalid_division;

  GST_DEBUG_OBJECT (midiparse, "format %u, tracks %u, division %u",
      format, ntracks, division);

  midiparse->ntracks = ntracks;
  midiparse->division = division;

  return TRUE;

invalid_format:
  {
    GST_ERROR_OBJECT (midiparse, "unsupported midi format %u", format);
    return FALSE;
  }
invalid_tracks:
  {
    GST_ERROR_OBJECT (midiparse, "invalid number of tracks %u for format %u",
        ntracks, format);
    return FALSE;
  }
invalid_division:
  {
    GST_ERROR_OBJECT (midiparse, "unsupported division");
    return FALSE;
  }
}
