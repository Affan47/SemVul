parse_vopdquant (GstBitReader * br, GstVC1FrameHdr * framehdr, guint8 dquant)
{
  GstVC1VopDquant *vopdquant = &framehdr->vopdquant;

  GST_DEBUG ("Parsing vopdquant");

  vopdquant->dqbilevel = 0;

  if (dquant == 2) {
    vopdquant->dquantfrm = 0;

    READ_UINT8 (br, vopdquant->pqdiff, 3);

    if (vopdquant->pqdiff != 7)
      vopdquant->altpquant = framehdr->pquant + vopdquant->pqdiff + 1;
    else {
      READ_UINT8 (br, vopdquant->abspq, 5);
      vopdquant->altpquant = vopdquant->abspq;
    }
  } else {
    READ_UINT8 (br, vopdquant->dquantfrm, 1);
    GST_DEBUG (" %u DquantFrm %u", gst_bit_reader_get_pos (br),
        vopdquant->dquantfrm);

    if (vopdquant->dquantfrm) {
      READ_UINT8 (br, vopdquant->dqprofile, 2);

      switch (vopdquant->dqprofile) {
        case GST_VC1_DQPROFILE_SINGLE_EDGE:
        case GST_VC1_DQPROFILE_DOUBLE_EDGES:
          READ_UINT8 (br, vopdquant->dqbedge, 2);
          break;

        case GST_VC1_DQPROFILE_ALL_MBS:
          READ_UINT8 (br, vopdquant->dqbilevel, 1);
          break;
      }

      if (vopdquant->dqbilevel
          || vopdquant->dqprofile != GST_VC1_DQPROFILE_ALL_MBS) {
        {
          READ_UINT8 (br, vopdquant->pqdiff, 3);

          if (vopdquant->pqdiff != 7)
            vopdquant->altpquant = framehdr->pquant + vopdquant->pqdiff + 1;
          else {
            READ_UINT8 (br, vopdquant->abspq, 5);
            vopdquant->altpquant = vopdquant->abspq;
          }
        }
      }
    }
  }

  return TRUE;

failed:
  GST_WARNING ("Failed to parse vopdquant");

  return FALSE;
}
