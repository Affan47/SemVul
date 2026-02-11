_request_lock(struct dlm_rsb *r, struct dlm_lkb *lkb)
{
	int error;


	error = set_master(r, lkb);
	if (error < 0)
		goto out;
	if (error) {
		error = 0;
		goto out;
	}

	if (is_remote(r)) {

		error = send_request(r, lkb);
	} else {
		error = do_request(r, lkb);


		do_request_effects(r, lkb, error);
	}
 out:
	return error;
}
