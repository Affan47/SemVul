ipxcp_resetci(f)
    fsm *f;
{
    wo->req_node = wo->neg_node && ao->neg_node;
    wo->req_nn	 = wo->neg_nn	&& ao->neg_nn;

    if (wo->our_network == 0) {
	wo->neg_node	   = 1;
	ao->accept_network = 1;
    }


    if (zero_node (wo->our_node)) {
	inc_node (wo->our_node);
	ao->accept_local = 1;
	wo->neg_node	 = 1;
    }


    if (zero_node (wo->his_node)) {
	inc_node (wo->his_node);
	ao->accept_remote = 1;
    }


    if (ao->router == 0) {
	ao->router |= BIT(RIP_SAP);
	wo->router |= BIT(RIP_SAP);
    }


    wo->neg_router = 1;


    *go = *wo;
}
