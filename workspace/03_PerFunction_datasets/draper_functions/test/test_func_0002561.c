credssp_new(rdpTransport* transport)
{
	rdpCredssp* self;

	self = (rdpCredssp*) xzalloc(sizeof(rdpCredssp));

	if (self != NULL)
	{
		self->transport = transport;
		self->send_seq_num = 0;
		self->ntlmssp = ntlmssp_new();
	}

	return self;
}
