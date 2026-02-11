socketBeginEncryption(mail::loginInfo &loginInfo)
{
#if HAVE_LIBCOURIERTLS

	string errmsg=starttls(loginInfo, true);

	if (errmsg.size() > 0)
	{
		loginInfo.callbackPtr->fail(errmsg);
		return false;
	}

	return establishtls();

#else


	loginInfo.callbackPtr->fail("SSL/TLS encryption not available.");
	return false;

#endif
}
