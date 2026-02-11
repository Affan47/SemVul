hpsa_is_pending_event(struct CommandList *c)
{
	return c->abort_pending || c->reset_pending;
}
