eel_register_operator(const char *name, eel_operator_cb_t handler,
		int priority, int retargs, int preargs)
{
	eel_symbol_t *s = _register(name, EST_OPERATOR, EDT_OPERATOR);
	if(!s)
		return -1;

	s->token = eel_get_unique_token();
	s->data.value.op.priority = priority;
	s->data.value.op.retargs = retargs;
	s->data.value.op.preargs = preargs;
	s->data.value.op.cb = handler;
	return s->token;
}
