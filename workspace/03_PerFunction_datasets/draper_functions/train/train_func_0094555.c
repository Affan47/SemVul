message_parse_received_date(hdr, hdrp)
char *hdr;
char **hdrp;
{
  char *curp, *hdrbuf = 0;


  if (*hdrp) return;


  message_parse_string(hdr, &hdrbuf);


  curp = hdrbuf + strlen(hdrbuf) - 1;
  while (curp > hdrbuf && *curp != ';')
    curp--;


  if (curp == hdrbuf) {
    *hdrp = hdrbuf;
    return;
  }


  curp++;
  message_parse_string(curp, hdrp);
  free(hdrbuf);
}
