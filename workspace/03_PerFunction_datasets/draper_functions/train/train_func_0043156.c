snd_mixart_kill_ref_pipe(struct mixart_mgr *mgr,
			     struct mixart_pipe *pipe, int monitoring)
{
	int err = 0;

	if(pipe->status == PIPE_UNDEFINED)
		return 0;

	if(monitoring)
		pipe->monitoring = 0;
	else
		pipe->references--;

	if((pipe->references <= 0) && (pipe->monitoring == 0)) {

		struct mixart_msg request;
		struct mixart_delete_group_resp delete_resp;


		err = mixart_set_clock( mgr, pipe, 0);
		if( err < 0 ) {
			dev_err(&mgr->pci->dev,
				"mixart_set_clock(0) return error!\n");
		}


		err = mixart_set_pipe_state(mgr, pipe, 0);
		if( err < 0 ) {
			dev_err(&mgr->pci->dev, "error stopping pipe!\n");
		}

		request.message_id = MSG_STREAM_DELETE_GROUP;
		request.uid = (struct mixart_uid){0,0};
		request.data = &pipe->group_uid;
		request.size = sizeof(pipe->group_uid);


		err = snd_mixart_send_msg(mgr, &request, sizeof(delete_resp), &delete_resp);
		if ((err < 0) || (delete_resp.status != 0)) {
			dev_err(&mgr->pci->dev,
				"error MSG_STREAM_DELETE_GROUP err(%x), status(%x)\n",
				err, delete_resp.status);
		}

		pipe->group_uid = (struct mixart_uid){0,0};
		pipe->stream_count = 0;
		pipe->status = PIPE_UNDEFINED;
	}

	return err;
}
