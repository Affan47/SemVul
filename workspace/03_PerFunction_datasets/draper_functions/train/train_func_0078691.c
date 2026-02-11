phone_exception(struct ast_channel *ast)
{
	int res;
	union telephony_exception phonee;
	struct phone_pvt *p = ast_channel_tech_pvt(ast);
	char digit;


	p->fr.datalen = 0;
	p->fr.samples = 0;
	p->fr.data.ptr =  NULL;
	p->fr.src = "Phone";
	p->fr.offset = 0;
	p->fr.mallocd=0;
	p->fr.delivery = ast_tv(0,0);

	phonee.bytes = ioctl(p->fd, PHONE_EXCEPTION);
	if (phonee.bits.dtmf_ready)  {
		ast_debug(1, "phone_exception(): DTMF\n");


		digit =  ioctl(p->fd, PHONE_GET_DTMF_ASCII);
		p->fr.subclass.integer = digit;
		p->fr.frametype = AST_FRAME_DTMF;
		return &p->fr;
	}
	if (phonee.bits.hookstate) {
		ast_debug(1, "Hookstate changed\n");
		res = ioctl(p->fd, PHONE_HOOKSTATE);

		ast_debug(1, "New hookstate: %d\n", res);
		if (!res && (p->mode != MODE_FXO))
			return NULL;
		else {
			if (ast_channel_state(ast) == AST_STATE_RINGING) {

				p->fr.frametype = AST_FRAME_CONTROL;
				p->fr.subclass.integer = AST_CONTROL_ANSWER;
				phone_setup(ast);
				ast_setstate(ast, AST_STATE_UP);
				return &p->fr;
			}  else
				ast_log(LOG_WARNING, "Got off hook in weird state %d\n", ast_channel_state(ast));
		}
	}
#if 1
	if (phonee.bits.pstn_ring)
		ast_verbose("Unit is ringing\n");
	if (phonee.bits.caller_id) {
		ast_verbose("We have caller ID\n");
	}
	if (phonee.bits.pstn_wink)
		ast_verbose("Detected Wink\n");
#endif

	p->fr.frametype = AST_FRAME_NULL;
	p->fr.subclass.integer = 0;
	return &p->fr;
}
