loginUseridResponse(int n, string msg)
{
	if ((n / 100) != 3)
	{
		error(msg);
		return;
	}

	installHandler(&mail::smtp::loginPasswdResponse);
	socketWrite(string(mail::encodebase64str(smtpLoginInfo.uid))
		    + "\r\n");
}
