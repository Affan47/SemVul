get_compat_ipmi_recv(struct ipmi_recv *p64,
				 struct compat_ipmi_recv __user *p32)
{
	compat_uptr_t tmp;

	if (!access_ok(VERIFY_READ, p32, sizeof(*p32)) ||
			__get_user(p64->recv_type, &p32->recv_type) ||
			__get_user(tmp, &p32->addr) ||
			__get_user(p64->addr_len, &p32->addr_len) ||
			__get_user(p64->msgid, &p32->msgid) ||
			get_compat_ipmi_msg(&p64->msg, &p32->msg))
		return -EFAULT;
	p64->addr = compat_ptr(tmp);
	return 0;
}
