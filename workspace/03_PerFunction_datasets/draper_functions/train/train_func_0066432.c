do_wait_block(sd_ack, pnh_packet, timeout_fn, pto_actual)

int			sd_ack;
struct nmsg		*pnh_packet;
void			(*timeout_fn)();
void			*pto_actual;

{
	timeout_fn_sv = timeout_fn;
	pto_actual_sv = pto_actual;

	if (frecv(pnh_packet)) lampanic("lamd (frecv)");

	if (kio_to(pto_actual, pto_actual ? to_handler : (void (*)()) 0))
			lampanic("lamd (kio_to)");

	kio_intr(sd_ack, ack_handler, FALSE);
}
