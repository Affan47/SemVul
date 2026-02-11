lockd_create_svc(void)
{
	struct svc_serv *serv;


	if (nlmsvc_rqst) {


		svc_get(nlmsvc_rqst->rq_server);
		return nlmsvc_rqst->rq_server;
	}


	if (nlmsvc_users)
		printk(KERN_WARNING
			"lockd_up: no pid, %d users??\n", nlmsvc_users);

	if (!nlm_timeout)
		nlm_timeout = LOCKD_DFLT_TIMEO;
	nlmsvc_timeout = nlm_timeout * HZ;

	serv = svc_create(&nlmsvc_program, LOCKD_BUFSIZE, &lockd_sv_ops);
	if (!serv) {
		printk(KERN_WARNING "lockd_up: create service failed\n");
		return ERR_PTR(-ENOMEM);
	}
	dprintk("lockd_up: service created\n");
	return serv;
}
