retrieve_msg_frame(struct mixart_mgr *mgr, u32 *msg_frame)
{

	u32 headptr, tailptr;

	tailptr = readl_be(MIXART_MEM(mgr, MSG_OUTBOUND_POST_TAIL));
	headptr = readl_be(MIXART_MEM(mgr, MSG_OUTBOUND_POST_HEAD));

	if (tailptr == headptr)
		return 0;

	if (tailptr < MSG_OUTBOUND_POST_STACK)
		return 0;
	if (tailptr >= MSG_OUTBOUND_POST_STACK + MSG_BOUND_STACK_SIZE)
		return 0;

	*msg_frame = readl_be(MIXART_MEM(mgr, tailptr));


	tailptr += 4;
	if( tailptr >= (MSG_OUTBOUND_POST_STACK+MSG_BOUND_STACK_SIZE) )
		tailptr = MSG_OUTBOUND_POST_STACK;
	writel_be(tailptr, MIXART_MEM(mgr, MSG_OUTBOUND_POST_TAIL));

	return 1;
}
