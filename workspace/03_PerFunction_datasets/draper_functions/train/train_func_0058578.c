sel_write_member(struct file *file, char *buf, size_t size)
{
	char *scon = NULL, *tcon = NULL;
	u32 ssid, tsid, newsid;
	u16 tclass;
	ssize_t length;
	char *newcon = NULL;
	u32 len;

	length = task_has_security(current, SECURITY__COMPUTE_MEMBER);
	if (length)
		goto out;

	length = -ENOMEM;
	scon = kzalloc(size + 1, GFP_KERNEL);
	if (!scon)
		goto out;

	length = -ENOMEM;
	tcon = kzalloc(size + 1, GFP_KERNEL);
	if (!tcon)
		goto out;

	length = -EINVAL;
	if (sscanf(buf, "%s %s %hu", scon, tcon, &tclass) != 3)
		goto out;

	length = security_context_str_to_sid(scon, &ssid, GFP_KERNEL);
	if (length)
		goto out;

	length = security_context_str_to_sid(tcon, &tsid, GFP_KERNEL);
	if (length)
		goto out;

	length = security_member_sid(ssid, tsid, tclass, &newsid);
	if (length)
		goto out;

	length = security_sid_to_context(newsid, &newcon, &len);
	if (length)
		goto out;

	length = -ERANGE;
	if (len > SIMPLE_TRANSACTION_LIMIT) {
		printk(KERN_ERR "SELinux: %s:  context size (%u) exceeds "
			"payload max\n", __func__, len);
		goto out;
	}

	memcpy(buf, newcon, len);
	length = len;
out:
	kfree(newcon);
	kfree(tcon);
	kfree(scon);
	return length;
}
