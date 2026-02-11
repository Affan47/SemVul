send_notoper(struct ParseState *state)
{
  if (state->done & DONE_NOTOPER)
    return;

  send_reply(state->sptr, (state->flags & MODE_PARSE_NOTOPER) ?
	     ERR_CHANOPRIVSNEEDED : ERR_NOTONCHANNEL, state->chptr->chname);

  state->done |= DONE_NOTOPER;
}
