do_request_effects(struct dlm_rsb *r, struct dlm_lkb *lkb,
			       int error)
{
	switch (error) {
	case -EAGAIN:
		if (force_blocking_asts(lkb))
			send_blocking_asts_all(r, lkb);
		break;
	case -EINPROGRESS:
		send_blocking_asts(r, lkb);
		break;
	}
}
