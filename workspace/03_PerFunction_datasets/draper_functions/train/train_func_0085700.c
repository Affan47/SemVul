get_compat_ipmi_msg(struct ipmi_msg *p64,
				struct compat_ipmi_msg __user *p32)
{
	compat_uptr_t tmp;

	if (!access_ok(VERIFY_READ, p32, sizeof(*p32)) ||
			__get_user(p64->netfn, &p32->netfn) ||
			__get_user(p64->cmd, &p32->cmd) ||
			__get_user(p64->data_len, &p32->data_len) ||
			__get_user(tmp, &p32->data))
		return -EFAULT;
	p64->data = compat_ptr(tmp);
	return 0;
}
