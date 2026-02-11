asyn_echoserver(IPC_Channel* wchan, int repcount)
{
	int		rdcount = 0;
	int		wrcount = 0;
	int		errcount = 0;
	int		blockedcount = 0;
	IPC_Message*	wmsg;
	const char*	w = "asyn_echoserver";
	int		stopsending = 0;

	cl_log(LOG_INFO, "Asyn echo server: %d reps pid %d."
	,	repcount, (int)getpid());

	(void)async_high_flow_callback;
	(void)async_low_flow_callback;


	wchan->ops->set_high_flow_callback(wchan, async_high_flow_callback, &stopsending);
	wchan->ops->set_low_flow_callback(wchan, async_low_flow_callback, &stopsending);

	wchan->low_flow_mark = 2;
	wchan->high_flow_mark = 20;

	while (rdcount < repcount) {
		int	rc;

		while (wrcount < repcount && blockedcount < 10
		       && wchan->ch_status != IPC_DISCONNECT
		       ){

			if (!stopsending){
				++wrcount;
				if (wrcount > repcount) {
					break;
				}
				wmsg = wchan->ops->new_ipcmsg(wchan, NULL, data_size, NULL);
				echomsgbody(wmsg->msg_body, data_size, wrcount, &wmsg->msg_len);
				if ((rc = wchan->ops->send(wchan, wmsg)) != IPC_OK){

					cl_log(LOG_INFO, "channel sstatus in echo server is %d",
					       wchan->ch_status);
					if (wchan->ch_status != IPC_CONNECT) {
						cl_log(LOG_ERR
						       ,	"asyn_echoserver: send failed"
						       " %d rc iter %d"
						       ,	rc, wrcount);
						++errcount;
						continue;
					}else {


						--wrcount;
					}
				}

				if (wchan->ops->is_sending_blocked(wchan)) {

					++blockedcount;
				}else{
					blockedcount = 0;
				}
			}


			errcount += checkinput(wchan, w, &rdcount, repcount);
			if (wrcount < repcount
			    &&	wchan->ch_status == IPC_DISCONNECT) {
				++errcount;
				break;
			}
		}


		wchan->ops->waitout(wchan);
		errcount += checkinput(wchan, w, &rdcount, repcount);
		if (wrcount >= repcount && rdcount < repcount) {
			while ((rc = wchan->ops->waitin(wchan)) == IPC_INTR);

			if (rc != IPC_OK) {
				cl_log(LOG_ERR
				       ,	"asyn_echoserver: waitin()"
				       " failed %d rc rdcount %d errno=%d"
				,	rc, rdcount, errno);
				cl_perror("waitin");
				exit(1);
			}
		}
		if (wchan->ch_status == IPC_DISCONNECT
		    &&	rdcount < repcount) {
			cl_log(LOG_ERR,
			       "asyn_echoserver: EOF in iter %d (wrcount=%d)",
			       rdcount, wrcount);
			EOFcheck(wchan);
			++errcount;
			break;
		}

		blockedcount = 0;

	}

	cl_log(LOG_INFO, "asyn_echoserver: %d errors", errcount);
#if 0
	cl_log(LOG_INFO, "%d destroying channel 0x%lx", getpid(), (unsigned long)wchan);
#endif
	wchan->ops->destroy(wchan); wchan = NULL;
	return errcount;
}
