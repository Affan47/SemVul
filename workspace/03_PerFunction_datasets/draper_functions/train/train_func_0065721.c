ack_handler()

{
	do_ack(&timeout_fn_sv, &pto_actual_sv);

	if (kio_to(pto_actual_sv, pto_actual_sv ? to_handler : (void (*)()) 0))
			lampanic("lamd (kio_to)");
}
