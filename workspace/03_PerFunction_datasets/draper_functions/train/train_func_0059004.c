Line_Count_2(WamWord sora_word, WamWord count_word)
{
  int stm;
  StmInf *pstm;
  int offset, char_count, line_count, line_pos;

  stm = Get_Stream_Or_Alias(sora_word, STREAM_CHECK_EXIST);
  pstm = stm_tbl[stm];

  if (!pstm->prop.text)
    Pl_Err_Permission(permission_operation_access,
		      permission_type_binary_stream, sora_word);

  Stream_Get_Position(pstm, &offset, &char_count, &line_count, &line_pos);

  return Un_Integer_Check(line_count, count_word);
}
