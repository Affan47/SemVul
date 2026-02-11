handle_request(int status)
{
	if (status == 0) {
		if (_audit_syscalladded) {
			fprintf(stderr, "Error - no list specified\n");
			return -1;
		}
		get_reply();
	} else if (status == -2)
		status = 0;
	else if (status > 0) {
		int rc;
		if (add != AUDIT_FILTER_UNSET) {

			if ((add & AUDIT_FILTER_MASK) != AUDIT_FILTER_TASK &&
					_audit_syscalladded != 1) {
					audit_rule_syscallbyname_data(
							rule_new, "all");
			}
			set_aumessage_mode(MSG_QUIET, DBG_NO);
			rc = audit_add_rule_data(fd, rule_new, add, action);
			set_aumessage_mode(MSG_STDERR, DBG_NO);

			if (rc < 0) {
				if (errno == EINVAL &&
				rule_new->fields[0] == AUDIT_DIR) {
					rule_new->fields[0] = AUDIT_WATCH;
					rc = audit_add_rule_data(fd, rule_new,
							add, action);
				} else {
					fprintf(stderr,
				"Error sending add rule data request (%s)\n",
					errno == EEXIST ?
					"Rule exists" : strerror(-rc));
				}
			}
		}
		else if (del != AUDIT_FILTER_UNSET) {
			if ((del & AUDIT_FILTER_MASK) != AUDIT_FILTER_TASK &&
					_audit_syscalladded != 1) {
					audit_rule_syscallbyname_data(
							rule_new, "all");
			}
			set_aumessage_mode(MSG_QUIET, DBG_NO);
			rc = audit_delete_rule_data(fd, rule_new,
								 del, action);
			set_aumessage_mode(MSG_STDERR, DBG_NO);

			if (rc < 0) {
				if (errno == EINVAL &&
					rule_new->fields[0] == AUDIT_DIR) {
					rule_new->fields[0] = AUDIT_WATCH;
					rc = audit_delete_rule_data(fd,rule_new,
								del, action);
				} else {
					fprintf(stderr,
			       "Error sending delete rule data request (%s)\n",
					errno == EEXIST ?
					"Rule exists" : strerror(-rc));
				}
			}
		} else {
        		usage();
	    		audit_close(fd);
			exit(1);
	    	}
		if (rc <= 0)
			status = -1;
		else
			status = 0;
	} else
		status = -1;

	audit_close(fd);
	fd = -1;
	return status;
}
