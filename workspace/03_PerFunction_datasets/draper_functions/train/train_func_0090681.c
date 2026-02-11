ooSendTCSandMSD(OOH323CallData *call)
{
	int ret;
	if(call->localTermCapState == OO_LocalTermCapExchange_Idle) {
		ret = ooSendTermCapMsg(call);
		if(ret != OO_OK) {
			OOTRACEERR3("ERROR:Sending Terminal capability message (%s, %s)\n",
				call->callType, call->callToken);
			return ret;
		}
	}

	return OO_OK;
}
