get_mpdf_data(FILE *fp, HTK_HMM_INFO *hmm, int mix_num, short stream_id)
{
  HTK_HMM_PDF *tmp = NULL;

  if (currentis("~p")) {

    read_token(fp);
    NoTokErr("missing macro name");
    tmp = mpdf_lookup(hmm, rdhmmdef_token);
    if (tmp == NULL) {
      jlog("Error: rdhmmdef_mpdf: ~p \"%s\" not defined\n", rdhmmdef_token);
      rderr(NULL);
    }
    if (mix_num != -1 && tmp->mix_num != mix_num) {
      jlog("Error: rdhmmdef_mpdf: mixture num in ~p \"%s\" definition and referer is different (%d != %d)\n", rdhmmdef_token, tmp->mix_num, mix_num);
      rderr(NULL);
    }
    if (tmp->stream_id != stream_id) {
      jlog("Error: rdhmmdef_mpdf: stream number in ~p \"%s\" definition and referer is different (%d != %d)\n", rdhmmdef_token, tmp->stream_id + 1, stream_id + 1);
      rderr(NULL);
    }
    read_token(fp);
  } else if (currentis("NUMMIXES")||currentis("MIXTURE")||currentis("TMIX")||currentis("MEAN")||currentis("~m")||currentis("RCLASS")) {

    tmp = mpdf_read(fp, hmm, mix_num);
    if (tmp->stream_id == -1) {
      tmp->stream_id = stream_id;
    } else if (tmp->stream_id != stream_id) {
      jlog("Error: rdhmmdef_mpdf: stream number exist in inline mpdf definition and referer is different (%d != %d)\n", rdhmmdef_token, tmp->stream_id + 1, stream_id + 1);
      rderr(NULL);
    }
    tmp->name = NULL;
    mpdf_add(hmm, tmp);
  } else {
    rderr("syntax error: not mixture pdf data");
  }
  return tmp;
}
