_get_request_token_session_cb           (SoupSession *session,
                                         SoupMessage *msg,
                                         gpointer data)
{
  g_assert (SOUP_IS_MESSAGE (msg));
  g_assert (data != NULL);


  _handle_soup_response (msg,
                         (FspParserFunc) fsp_parser_get_request_token,
                         data);
}
