XTestFakeInput(


register Display	*dpy,


char			*action_list_addr,


int			action_list_size,


int			ack_flag)
{


	xTestFakeInputReq	*req;


	int			i;

	LockDisplay(dpy);
	if ((XTestCheckExtInit(dpy) == -1) ||
	    (action_list_size > XTestMAX_ACTION_LIST_SIZE))
	{


		UnlockDisplay(dpy);
		return(-1);
	}
	else
	{


		GetReq(TestFakeInput, req);


		req->reqType = XTestReqCode;


		req->XTestReqType = X_TestFakeInput;


		req->ack = ack_flag;


		for (i = 0; i < XTestMAX_ACTION_LIST_SIZE; i++)
		{
			req->action_list[i] = 0;
		}


		for (i = 0; i < action_list_size; i++)
		{
			req->action_list[i] = *(action_list_addr++);
		}
		UnlockDisplay(dpy);
		SyncHandle();
		return(0);
	}
}
