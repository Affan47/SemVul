getnameinfo_result(s48_call_t call, struct getnameinfo_handshake* handshake)
{
  s48_ref_t sch_result;

  if (handshake->status != 0)
    {
      int status = handshake->status;
      free(handshake);
      s48_error_2(call, "s48_getnameinfo_result", gai_strerror(status), 0);
    }


  sch_result = s48_make_vector_2(call, 2, s48_unspecific_2(call));
  s48_vector_set_2(call, sch_result, 0, s48_enter_string_latin_1_2(call, handshake->host));
  s48_vector_set_2(call, sch_result, 1, s48_enter_string_latin_1_2(call, handshake->serv));

  free(handshake);

  return sch_result;
}
