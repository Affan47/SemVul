Set_Stream_Line_Column_3(WamWord sora_word, WamWord line_word,
			 WamWord col_word)
{
  int stm;
  StmInf *pstm;
  int line_count, line_pos;


  stm = Get_Stream_Or_Alias(sora_word, STREAM_CHECK_EXIST);
  pstm = stm_tbl[stm];

  if (!pstm->prop.reposition)
    Pl_Err_Permission(permission_operation_reposition,
		      permission_type_stream, sora_word);

  if (!pstm->prop.text)
    Pl_Err_Permission(permission_operation_reposition,
		      permission_type_binary_stream, sora_word);


  line_count = Rd_Integer_Check(line_word) - 1;
  line_pos = Rd_Integer_Check(col_word) - 1;

  return line_count >= 0 && line_pos >= 0 &&
    Stream_Set_Position_LC(pstm, line_count, line_pos) == 0;
}
