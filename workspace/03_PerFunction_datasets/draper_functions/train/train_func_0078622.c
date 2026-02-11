echoSCP(T_ASC_Association *assoc, T_DIMSE_Message *msg, T_ASC_PresentationContextID presID) {
	CONDITION cond;


	cond = DIMSE_sendEchoResponse(assoc, presID, &msg->msg.CEchoRQ, STATUS_Success, NULL);

	return cond;
}
