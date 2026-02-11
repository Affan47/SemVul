init_ecryptfs_cipher_param_node()
{
	struct cipher_descriptor *cd = cipher_descriptors;
	int rc = 0;

	while (cd && cd->name) {
		struct transition_node *tn;

		if (ecryptfs_cipher_param_node.num_transitions
		    >= MAX_NUM_TRANSITIONS) {
			syslog(LOG_WARNING, "%s: Exceeded maximum number of "
			       "transition nodes [%d] whilst constructing "
			       "cipher list\n", __FUNCTION__,
			       MAX_NUM_TRANSITIONS);
			goto out;
		}
		tn = &ecryptfs_cipher_param_node.tl[
			ecryptfs_cipher_param_node.num_transitions];
		rc = asprintf(&tn->val, "%s", cd->name);
		if (rc == -1) {
			rc = -ENOMEM;
			goto out;
		}
		rc = 0;
		if (!ecryptfs_cipher_param_node.suggested_val) {
			rc = asprintf(&ecryptfs_cipher_param_node.suggested_val,
				      "%s", cd->name);
			if (rc == -1) {
				rc = -ENOMEM;
				goto out;
			}
			rc = 0;
		}
		rc = asprintf(&tn->pretty_val, "%s: blocksize = %d; "
			      "min keysize = %d; max keysize = %d", cd->name,
			      cd->blocksize, cd->min_keysize, cd->max_keysize);
		if (rc == -1) {
			rc = -ENOMEM;
			goto out;
		}
		rc = 0;
		tn->next_token = &ecryptfs_key_bytes_param_node;
		tn->trans_func = tf_ecryptfs_cipher;
		ecryptfs_cipher_param_node.num_transitions++;
		cd++;
	}
out:
	return rc;
}
