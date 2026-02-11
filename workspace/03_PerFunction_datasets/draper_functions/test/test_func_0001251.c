ssh_do_close(Ssh ssh, int notify_exit)
{
    int ret = 0;
    struct ssh_channel *c;

    ssh->state = SSH_STATE_CLOSED;
    expire_timer_context(ssh);
    if (ssh->s) {
        sk_close(ssh->s);
        ssh->s = NULL;
        if (notify_exit)
            notify_remote_exit(ssh->frontend);
        else
            ret = 1;
    }


    if (ssh->channels) {
	while (NULL != (c = index234(ssh->channels, 0))) {
	    switch (c->type) {
	      case CHAN_X11:
		x11_close(c->u.x11.s);
		break;
	      case CHAN_SOCKDATA:
	      case CHAN_SOCKDATA_DORMANT:
		pfd_close(c->u.pfd.s);
		break;
	    }
	    del234(ssh->channels, c);
	    if (ssh->version == 2)
		bufchain_clear(&c->v.v2.outbuffer);
	    sfree(c);
	}
    }


    if (ssh->portfwds) {
	struct ssh_portfwd *pf;
	while (NULL != (pf = index234(ssh->portfwds, 0))) {

	    if (pf->local)
		pfd_terminate(pf->local);
	    del234(ssh->portfwds, pf);
	    free_portfwd(pf);
	}
	freetree234(ssh->portfwds);
	ssh->portfwds = NULL;
    }

    return ret;
}
