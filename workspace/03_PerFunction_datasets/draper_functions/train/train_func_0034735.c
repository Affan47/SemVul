nonExternalLogin()
{
	if (!myserver->pop3LoginInfo.loginCallbackFunc)
	{
		loginCallbackPwd(myserver->pop3LoginInfo.pwd);
		return;
	}

	currentHandler=NULL;
	if (myserver->pop3LoginInfo.uid.size() > 0)
	{
		loginCallbackUid(myserver->pop3LoginInfo.uid);
		return;
	}

	login_callback_handler= &mail::pop3::LoginTask::loginCallbackUid;
	currentCallback=myserver->pop3LoginInfo.loginCallbackFunc;
	currentCallback->target=this;
	currentCallback->getUserid();
}
