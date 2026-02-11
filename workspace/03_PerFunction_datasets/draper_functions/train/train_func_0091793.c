_Csec_print_token(tok)
     csec_buffer_t tok;
{
  int i,l=0;
  char buf[50];
  struct Csec_api_global_info *glip;
  unsigned char *p = tok->value;

  if (Csec_init_globals (&glip))
    return;

  if (!glip->trace_mode)
    return;

  for (i=0; i < tok->length; i++, p++) {
  	sprintf(buf+l,"%02x ",*p);
    l+=3;
    if(l>=48) {
          Csec_trace(NULL, "%s\n",buf);
          l=0;
    	}
    }
   if(l)  Csec_trace(NULL, "%s\n",buf);
   Csec_trace(NULL,"\n");
}
