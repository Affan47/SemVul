get_ppi(decode_proto_t *dp)
{
  static const linktype_data_t *pph_lkentry = NULL;
  guint16 pph_len;
  guint32 pph_dlt;
  int i;

  if (dp->cur_len < 64)
    {
      g_warning (_("PPI:captured size too small, packet discarded"));
      decode_proto_add(dp, "PPI");
      return;
    }


#ifdef WORDS_BIGENDIAN
  pph_len = phtons(dp->cur_packet+2);
  pph_dlt = phtonl(dp->cur_packet+4);
#else
  pph_len = *(guint16 *)(dp->cur_packet+2);
  pph_dlt = *(guint32 *)(dp->cur_packet+4);
#endif

  add_offset(dp, pph_len);

  if (!pph_lkentry || pph_lkentry->dlt_linktype != pph_dlt)
    {
      pph_lkentry = NULL;
      for (i = 0; linktypes[i].lt_desc != NULL ; ++i)
        {
          if (linktypes[i].dlt_linktype == pph_dlt)
            {
              pph_lkentry = linktypes + i;
              pph_lkentry->fun(dp);
            }
        }
      g_warning (_("PPI:unsupported link type %u, packet discarded"), pph_dlt);
      return;
    }
  pph_lkentry->fun(dp);
}
