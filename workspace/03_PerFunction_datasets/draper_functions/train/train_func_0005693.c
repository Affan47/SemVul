transmit_callstate(struct skinny_device *d, int buttonInstance, unsigned callid, int state)
{
	struct skinny_req *req;

	if (!(req = req_alloc(sizeof(struct call_state_message), CALL_STATE_MESSAGE)))
		return;

	req->data.callstate.callState = htolel(state);
	req->data.callstate.lineInstance = htolel(buttonInstance);
	req->data.callstate.callReference = htolel(callid);

	SKINNY_DEBUG(DEBUG_PACKET, 3, "Transmitting CALL_STATE_MESSAGE to %s, state %s, inst %d, callid %d\n",
		d->name, callstate2str(state), buttonInstance, callid);
	transmit_response(d, req);
}
