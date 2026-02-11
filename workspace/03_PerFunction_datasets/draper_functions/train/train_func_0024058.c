cifs_security_flags_proc_write(struct file *file,
		const char __user *buffer, size_t count, loff_t *ppos)
{
	int rc;
	unsigned int flags;
	char flags_string[12];
	bool bv;

	if ((count < 1) || (count > 11))
		return -EINVAL;

	memset(flags_string, 0, 12);

	if (copy_from_user(flags_string, buffer, count))
		return -EFAULT;

	if (count < 3) {

		if (strtobool(flags_string, &bv) == 0) {
			global_secflags = bv ? CIFSSEC_MAX : CIFSSEC_DEF;
			return count;
		} else if (!isdigit(flags_string[0])) {
			cifs_dbg(VFS, "Invalid SecurityFlags: %s\n",
					flags_string);
			return -EINVAL;
		}
	}


	rc = kstrtouint(flags_string, 0, &flags);
	if (rc) {
		cifs_dbg(VFS, "Invalid SecurityFlags: %s\n",
				flags_string);
		return rc;
	}

	cifs_dbg(FYI, "sec flags 0x%x\n", flags);

	if (flags == 0)  {
		cifs_dbg(VFS, "Invalid SecurityFlags: %s\n", flags_string);
		return -EINVAL;
	}

	if (flags & ~CIFSSEC_MASK) {
		cifs_dbg(VFS, "Unsupported security flags: 0x%x\n",
			 flags & ~CIFSSEC_MASK);
		return -EINVAL;
	}

	cifs_security_flags_handle_must_flags(&flags);


	global_secflags = flags;
	if (global_secflags & CIFSSEC_MUST_SIGN) {

		global_secflags |= CIFSSEC_MAY_SIGN;
		cifs_dbg(FYI, "packet signing now required\n");
	} else if ((global_secflags & CIFSSEC_MAY_SIGN) == 0) {
		cifs_dbg(FYI, "packet signing disabled\n");
	}

	return count;
}
