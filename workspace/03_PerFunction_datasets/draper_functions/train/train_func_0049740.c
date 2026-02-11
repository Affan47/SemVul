ppp_fsm_recv_conf_req_ack(struct ppp_fsm_t *layer)
{
	switch(layer->fsm_state)
	{
		case FSM_Closed:
			layer->send_term_ack(layer);
			break;
		case FSM_Stopped:

			init_req_counter(layer,layer->max_configure);
			--layer->restart_counter;
			if (layer->send_conf_req) layer->send_conf_req(layer);
		case FSM_Req_Sent:
		case FSM_Ack_Sent:
			if (layer->send_conf_ack) layer->send_conf_ack(layer);
			layer->fsm_state=FSM_Ack_Sent;
			break;
		case FSM_Ack_Rcvd:
			if (layer->send_conf_ack) layer->send_conf_ack(layer);
			stop_timer(layer);
			if (layer->layer_up) layer->layer_up(layer);
			layer->fsm_state=FSM_Opened;
			break;
		case FSM_Opened:
			if (layer->layer_down) layer->layer_down(layer);
			--layer->restart_counter;
			if (layer->send_conf_req) layer->send_conf_req(layer);
			if (layer->send_conf_ack) layer->send_conf_ack(layer);
			layer->fsm_state=FSM_Ack_Sent;
			break;
		default:
			break;
	}
}
