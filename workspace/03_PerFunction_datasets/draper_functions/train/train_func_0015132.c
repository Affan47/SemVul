Set_Stream_Eof_Action_2(WamWord sora_word, WamWord action_word)
{
  int stm;
  StmInf *pstm;

  stm = Get_Stream_Or_Alias(sora_word, STREAM_CHECK_EXIST);
  pstm = stm_tbl[stm];

  if (pstm->prop.output)
    Pl_Err_Permission(permission_operation_modify,
		      permission_type_stream, sora_word);

  pstm->prop.eof_action = Rd_Integer_Check(action_word);
}
