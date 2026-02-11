jd_wsch (yomi, jbuf, jbuf_siz, kbuf, kbuf_siz)
     w_char *yomi, *kbuf;
     JISHOJOHO *jbuf;
     int jbuf_siz, kbuf_siz;
{
  register int i, klen;
  register w_char *b;

  struct wnn_jdata *jdp;
  int len;
  int cnt;

  JD_WNN_DEAD if ((cnt = jl_word_search_by_env (buf, yomi, &jdp)) < 0)
    return (-1);

  if (cnt >= jbuf_siz - 1)
    {
      wnn_errorno = WNN_JISHOTABLE_FULL;
      return (-1);
    }
  for (klen = 0, i = cnt, b = kbuf; i > 0; jbuf++, jdp++, i--)
    {
      jbuf->hindo = jdp->hindo;
#ifdef  NEW_HINSI
      jbuf->bumpo = jdp->hinshi;
#else
      jbuf->bumpo = newh_to_oldh (jdp->hinshi);
#endif
      jbuf->jisho = jdp->dic_no;
      jbuf->serial = jdp->serial;
      jbuf->k_data = b;
      len = wnn_Strlen (jdp->kanji) + 1;
      klen += len;
      if (klen >= kbuf_siz)
        {
          wnn_errorno = WNN_JISHOTABLE_FULL;
          return (-1);
        }
      wnn_Strcpy (b, jdp->kanji);
      b += len;
    }
  jbuf->hindo = -1;
  return cnt;
}
