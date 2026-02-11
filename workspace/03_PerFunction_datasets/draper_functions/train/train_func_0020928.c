Assoc_Socket_Streams_3(WamWord socket_word,
		       WamWord stm_in_word, WamWord stm_out_word)
{
  int stm_in, stm_out;
  char stream_name[256];

  int sock = Rd_Integer_Check(socket_word);

  sprintf(stream_name, "socket_stream(assoc(%d))", sock);
  if (!Create_Socket_Streams(sock, stream_name, &stm_in, &stm_out))
    return FALSE;

  Get_Integer(stm_in, stm_in_word);
  Get_Integer(stm_out, stm_out_word);
  return TRUE;
}
