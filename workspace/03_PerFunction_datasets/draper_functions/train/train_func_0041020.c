rocker_port_stp_update(struct rocker_port *rocker_port,
				  struct switchdev_trans *trans, int flags,
				  u8 state)
{
	bool want[ROCKER_CTRL_MAX] = { 0, };
	bool prev_ctrls[ROCKER_CTRL_MAX];
	u8 uninitialized_var(prev_state);
	int err;
	int i;

	if (switchdev_trans_ph_prepare(trans)) {
		memcpy(prev_ctrls, rocker_port->ctrls, sizeof(prev_ctrls));
		prev_state = rocker_port->stp_state;
	}

	if (rocker_port->stp_state == state)
		return 0;

	rocker_port->stp_state = state;

	switch (state) {
	case BR_STATE_DISABLED:

		break;
	case BR_STATE_LISTENING:
	case BR_STATE_BLOCKING:
		want[ROCKER_CTRL_LINK_LOCAL_MCAST] = true;
		break;
	case BR_STATE_LEARNING:
	case BR_STATE_FORWARDING:
		if (!rocker_port_is_ovsed(rocker_port))
			want[ROCKER_CTRL_LINK_LOCAL_MCAST] = true;
		want[ROCKER_CTRL_IPV4_MCAST] = true;
		want[ROCKER_CTRL_IPV6_MCAST] = true;
		if (rocker_port_is_bridged(rocker_port))
			want[ROCKER_CTRL_DFLT_BRIDGING] = true;
		else if (rocker_port_is_ovsed(rocker_port))
			want[ROCKER_CTRL_DFLT_OVS] = true;
		else
			want[ROCKER_CTRL_LOCAL_ARP] = true;
		break;
	}

	for (i = 0; i < ROCKER_CTRL_MAX; i++) {
		if (want[i] != rocker_port->ctrls[i]) {
			int ctrl_flags = flags |
					 (want[i] ? 0 : ROCKER_OP_FLAG_REMOVE);
			err = rocker_port_ctrl(rocker_port, trans, ctrl_flags,
					       &rocker_ctrls[i]);
			if (err)
				goto err_out;
			rocker_port->ctrls[i] = want[i];
		}
	}

	err = rocker_port_fdb_flush(rocker_port, trans, flags);
	if (err)
		goto err_out;

	err = rocker_port_fwding(rocker_port, trans, flags);

err_out:
	if (switchdev_trans_ph_prepare(trans)) {
		memcpy(rocker_port->ctrls, prev_ctrls, sizeof(prev_ctrls));
		rocker_port->stp_state = prev_state;
	}

	return err;
}
