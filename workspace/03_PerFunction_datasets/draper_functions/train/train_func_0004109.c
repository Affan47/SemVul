startExec()
{
	static void (*op_func[])() = {
		OpStart, OpSaveStatus, OpSaveStatusAll, OpVerifyApp, OpExitProcess,
		OpGetStatus, OpGetState, OpGetAppstate, OpKill, OpKillAll,
		OpFddChangeProc, OpGetProclist, OpGetHandlerlist, OpGetCpulist,
		OpExit
	};
	u_short this_op;
	int sockssh;
   	char exit_info;


	if (debug) printf("in DAC_startExec term_flag: (%d)\n", term_flag);

	while (!term_flag) {

		if ((newsock = get_connection(oldsock, NULL)) == -1)
		{
			printf(" Network problem. Try it later. \n");
   			send_cid_appstatus(hostname, APP_KILLED);
			exit(E_CONNECT);
		}

		if (!readn(newsock, (char *)&this_op, sizeof(u_short))) {
			close(newsock);
			continue;
		}
		this_op = ntohs(this_op);

		if (this_op >= DAC_OP_MIN && this_op <= DAC_OP_MAX)
			(*op_func[this_op - DAC_OP_MIN])();
		close(newsock);
	}

        killAllProcesses();
        cleanAllProcesses();
        killAllHandlers();
        unmapDacport();

        if ((sockssh = get_socket()) != -1)
                if (do_connect(sockssh, sng_gethostid(), ssh_port)) {

			if (debug) printf("DAC sending exit_flag\n");

			exit_info = APP_EXITTED;
                        writen(sockssh, (char *)&exit_info, sizeof(char));
		}

	if (debug) printf("DAC exit\n");

}
