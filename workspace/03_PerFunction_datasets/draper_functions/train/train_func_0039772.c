zero_req_counter(struct ppp_fsm_t *layer)
{
	layer->restart_counter=0;

	if (!layer->restart_timer.tpd)
		triton_timer_add(layer->ppp->ses.ctrl->ctx, &layer->restart_timer, 0);
}
