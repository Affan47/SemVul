tf_pass_file(struct ecryptfs_ctx *ctx, struct param_node *node,
			struct val_node **head, void **foo)
{
	char *tmp_val = NULL;
	int fd;
	struct ecryptfs_name_val_pair *file_head;
	struct ecryptfs_name_val_pair *walker;
	int rc = 0;

	if (strcmp(node->mnt_opt_names[0], "passphrase_passwd_file") == 0) {
		fd = open(node->val, O_RDONLY);
		if (fd == -1) {
			rc = -errno;
			syslog(LOG_ERR, "%s: Error whilst attempting to open "
			       "[%s]; errno = [%m]\n", __FUNCTION__, node->val);
			goto out;
		}
	} else if (strcmp(node->mnt_opt_names[0], "passphrase_passwd_fd") == 0) {
		fd = strtol(node->val, NULL, 0);
	} else {
		syslog(LOG_ERR, "%s: Invalid file descriptor qualifier\n",
			__FUNCTION__);
		rc = MOUNT_ERROR;
		goto out;
	}
	file_head = malloc(sizeof(struct ecryptfs_name_val_pair));
	if (!file_head) {
		close(fd);
		rc = -ENOMEM;
		goto out;
	}
	memset(file_head, 0, sizeof(struct ecryptfs_name_val_pair));
	rc = parse_options_file(fd, file_head);
	close(fd);
	if (rc) {
		syslog(LOG_ERR, "%s: Error parsing file for passwd; "
		       "rc = [%d]\n", __FUNCTION__, rc);
		goto out;
	}
	walker = file_head->next;
	while (walker) {
		if (strcmp(walker->name, "passphrase_passwd") == 0
		    || strcmp(walker->name, "passwd") == 0) {
			if (asprintf(&tmp_val, "%s", walker->value) < 0) {
				rc = -ENOMEM;
				goto out;
			}
			stack_push(head, tmp_val);
			break;
		}
		walker = walker->next;
	}
	if (!walker) {
		syslog(LOG_ERR, "%s: Cannot find [passwd] directive\n",
		       __FUNCTION__);
		rc = MOUNT_ERROR;
		goto out;
	}
	free_name_val_pairs(file_head);
	file_head = NULL;
	walker = NULL;
out:
	free(node->val);
	node->val = NULL;
	return rc;
}
