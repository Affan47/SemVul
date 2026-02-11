__niu_set_and_wait_clear_mac(struct niu *np, unsigned long reg,
					u64 bits, int limit, int delay,
					const char *reg_name)
{
	int err;

	nw64_mac(reg, bits);
	err = __niu_wait_bits_clear_mac(np, reg, bits, limit, delay);
	if (err)
		netdev_err(np->dev, "bits (%llx) of register %s would not clear, val[%llx]\n",
			   (unsigned long long)bits, reg_name,
			   (unsigned long long)nr64_mac(reg));
	return err;
}
