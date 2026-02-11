coverart_read_results(int sock, struct art_query *query)
{
  char inbuffer[512];

  cdindex_read_line(sock, inbuffer, 512);
  if(strcmp("NumMatches: 0", inbuffer) == 0 ||
     strncmp("NumMatches: ", inbuffer, 12) != 0) {
    query->query_match = QUERY_NOMATCH;
    query->query_matches = 0;
    return 0;
  }

  do
    coverart_process_line(inbuffer, query);
  while(cdindex_read_line(sock, inbuffer, 512) > -1);

  return 0;
}
