inet_udp_got_unsolicited_incoming(void)
{
	if (outgoing_udp_state != UNSOLICITED_OFF) {
		if (GNET_PROPERTY(fw_debug))
			g_debug("FW: got unsolicited UDP message => not firewalled");
		move_to_unsolicited_off();
	} else if (GNET_PROPERTY(is_udp_firewalled)) {
		if (GNET_PROPERTY(fw_debug))
			g_debug("FW: got unsolicited UDP message");
	}

	inet_switch_to_udp_not_firewalled();
	wd_kick(incoming_udp_wd);
}
