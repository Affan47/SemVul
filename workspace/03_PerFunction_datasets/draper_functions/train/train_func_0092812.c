XTestGetInput(


register Display	*dpy,


int			action_handling)
{


	xTestGetInputReq 	*req;

	LockDisplay(dpy);
	if (XTestCheckExtInit(dpy) == -1)
	{


		UnlockDisplay(dpy);
		return(-1);
	}
	else
	{


		GetReq(TestGetInput, req);


		req->reqType = XTestReqCode;


		req->XTestReqType = X_TestGetInput;


		req->mode = action_handling;
		UnlockDisplay(dpy);
		SyncHandle();
		return(0);
	}
}
