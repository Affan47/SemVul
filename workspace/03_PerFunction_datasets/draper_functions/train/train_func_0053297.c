Tfddretrievetuple(handler_list, deadhost)
handlerinfo_t *handler_list;
host_t *deadhost;
{
        tsh_retrieve_it out;
        handlerinfo_t *p_q;
        int tsh_sock;
	u_short tshop;
        u_short tsh_port;

        out.host = deadhost->hostid;
	out.proc_id = htonl(deadhost->proc_id);
        p_q = handler_list;
        tshop = htons(TSH_OP_RETRIEVE);

        while (p_q != NULL) {
            if (p_q->type == 't') {
		p_q->host = inet_addr(p_q->inet_addr);
                if ((tsh_port = sngd_getmap(p_q->mapid, p_q->host, p_q->login, PMD_PROT_TCP)) == 0) {
                        perror("DACLIB_fddretrievetuple::sngd_getmap\n");
                        return(0);
                }
                if ((tsh_sock = get_socket()) == -1) {
                        perror("DACLIB_fddretrievetuple::get_socket\n") ;
                        return(0);
                }
printf(" FDD: -- Automatic Tuple Recovery: TShost(%u) id(%s)\n", p_q->host,
		p_q->mapid);
                if (!do_connect(tsh_sock, p_q->host, tsh_port)) {
                        perror("DACLIB_fddretrievetuple::do_connect\n");
                        return(0);
                }
                if (!writen(tsh_sock, (char *)&tshop, sizeof(u_short))) {
                        close(tsh_sock);
                        return(0);
		}
                if(!writen(tsh_sock, (char *)&out, sizeof(tsh_retrieve_it))) {
                        close(tsh_sock);
                        return(0);
                }

                close(tsh_sock);
	    }
            p_q = p_q->next;
        }
        return(1);
}
