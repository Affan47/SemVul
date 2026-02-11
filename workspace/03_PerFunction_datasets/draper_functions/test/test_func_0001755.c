tid_send(sd)
int sd;
{
  tsh_tidinfo_ot out;
  space2_t *p_q;

  p_q = tsh.retrieve;
  while (p_q != NULL) {
	out.status = 1;
	out.tid_host = (p_q->host);
	out.tid_cid_port = (p_q->cidport);
	strcpy(out.tid, p_q->name);


       	if (!writen(sd, (char *)&out, sizeof(tsh_tidinfo_ot))) return ;
        p_q = p_q->next;
  }
  return;

}
