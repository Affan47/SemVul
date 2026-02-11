TMixHelo(void *p)
{
	INIT_STACK;
	BEGIN_STACK("CAInfoService::TMixHelo");

	InfoServiceHeloMsg* message = (InfoServiceHeloMsg*)p;
	if (message->is->sendMixHelo(message->strXML, message->len, message->requestCommand, message->param, message->addr) == E_SUCCESS)
	{
		FINISH_STACK("CAInfoService::TMixHelo");
		THREAD_RETURN_SUCCESS;
	}
	FINISH_STACK("CAInfoService::TMixHelo");
	THREAD_RETURN_SUCCESS;
}
