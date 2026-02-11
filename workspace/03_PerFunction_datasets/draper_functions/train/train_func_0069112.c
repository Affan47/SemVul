niu_led_state_restore(struct niu *np, u64 val)
{
	if (np->flags & NIU_FLAGS_XMAC)
		nw64_mac(XMAC_CONFIG, val);
	else
		nw64_mac(BMAC_XIF_CONFIG, val);
}
