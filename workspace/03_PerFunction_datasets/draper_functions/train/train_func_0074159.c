msg_free(message_data_t *m)
{
    int i;

    if (m->data) {
	prot_free(m->data);
    }
    if (m->f) {
	fclose(m->f);
    }
    if (m->id) {
	free(m->id);
    }

    if (m->return_path) {
	free(m->return_path);
    }
    if (m->rcpt) {
	for (i = 0; i < m->rcpt_num; i++) {
	    if (m->rcpt[i]->all) free(m->rcpt[i]->all);
	    if (m->rcpt[i]->rcpt) free(m->rcpt[i]->rcpt);
	    free(m->rcpt[i]);
	}
	free(m->rcpt);
    }
    if (m->date) {
      free(m->date);
     }

    if (m->authuser) {
	free(m->authuser);
	if (m->authstate) auth_freestate(m->authstate);
    }

    spool_free_hdrcache(m->hdrcache);

    free(m);
}
