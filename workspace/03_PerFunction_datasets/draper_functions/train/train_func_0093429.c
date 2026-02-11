Set_Stream_Type_2(WamWord sora_word, WamWord is_text_word)
{
  int stm;
  StmInf *pstm;
  int text;

  stm = Get_Stream_Or_Alias(sora_word, STREAM_CHECK_EXIST);
  pstm = stm_tbl[stm];

  text = Rd_Integer_Check(is_text_word);
  if ((unsigned) text == pstm->prop.text)
    return;

  if (pstm->char_count)
    Pl_Err_Permission(permission_operation_modify,
		      permission_type_stream, sora_word);

  pstm->prop.text = text;
#if defined(_WIN32) || defined(__CYGWIN__)
  {
    FILE *f;

    f = Stdio_Desc_Of_Stream(stm);
    if (f == NULL)
      return;

    setmode(fileno(f), (text) ? O_TEXT : O_BINARY);
  }
#endif
}
