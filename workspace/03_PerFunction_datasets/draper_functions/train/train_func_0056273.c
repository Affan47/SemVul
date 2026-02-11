aa_check_perms(struct aa_profile *profile, struct aa_perms *perms,
		   u32 request, struct common_audit_data *sa,
		   void (*cb) (struct audit_buffer *, void *))
{
	int type, error;
	bool stop = false;
	u32 denied = request & (~perms->allow | perms->deny);
	if (likely(!denied)) {

		request &= perms->audit;
		if (!request || !sa)
			return 0;

		type = AUDIT_APPARMOR_AUDIT;
		error = 0;
	} else {
		error = -EACCES;

		if (denied & perms->kill)
			type = AUDIT_APPARMOR_KILL;
		else if (denied == (denied & perms->complain))
			type = AUDIT_APPARMOR_ALLOWED;
		else
			type = AUDIT_APPARMOR_DENIED;

		if (denied & perms->stop)
			stop = true;
		if (denied == (denied & perms->hide))
			error = -ENOENT;

		denied &= ~perms->quiet;
		if (!sa || !denied)
			return error;
	}

	if (sa) {
		aad(sa)->label = &profile->label;
		aad(sa)->request = request;
		aad(sa)->denied = denied;
		aad(sa)->error = error;
		aa_audit_msg(type, sa, cb);
	}

	if (type == AUDIT_APPARMOR_ALLOWED)
		error = 0;

	return error;
}
