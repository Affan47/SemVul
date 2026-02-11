invokeMenuMethod(AV_View * pView,
							   EV_EditMethod * pEM,
							   const UT_String& stScriptName)
{
	UT_return_val_if_fail(pEM,false);
	EV_EditMethodType t = pEM->getType();
	if (!(t & EV_EMT_APP_METHOD)) {
		UT_ASSERT(pView);
	}
	if ((t & EV_EMT_REQUIREDATA) && stScriptName.size() == 0)
	{
		UT_DEBUGMSG(("    invoke aborted due to lack of script name\n"));
		return false;
	}

	EV_EditMethodCallData emcd(stScriptName);
	pEM->Fn(pView, &emcd);

	return true;
}
