fcoe_ctlr_vn_timeout(struct fcoe_ctlr *fip)
{
	unsigned long next_time;
	u8 mac[ETH_ALEN];
	u32 new_port_id = 0;

	mutex_lock(&fip->ctlr_mutex);
	switch (fip->state) {
	case FIP_ST_VNMP_START:
		fcoe_ctlr_set_state(fip, FIP_ST_VNMP_PROBE1);
		fcoe_ctlr_vn_send(fip, FIP_SC_VN_PROBE_REQ, fcoe_all_vn2vn, 0);
		next_time = jiffies + msecs_to_jiffies(FIP_VN_PROBE_WAIT);
		break;
	case FIP_ST_VNMP_PROBE1:
		fcoe_ctlr_set_state(fip, FIP_ST_VNMP_PROBE2);
		fcoe_ctlr_vn_send(fip, FIP_SC_VN_PROBE_REQ, fcoe_all_vn2vn, 0);
		next_time = jiffies + msecs_to_jiffies(FIP_VN_ANN_WAIT);
		break;
	case FIP_ST_VNMP_PROBE2:
		fcoe_ctlr_set_state(fip, FIP_ST_VNMP_CLAIM);
		new_port_id = fip->port_id;
		hton24(mac, FIP_VN_FC_MAP);
		hton24(mac + 3, new_port_id);
		fcoe_ctlr_map_dest(fip);
		fip->update_mac(fip->lp, mac);
		fcoe_ctlr_vn_send_claim(fip);
		next_time = jiffies + msecs_to_jiffies(FIP_VN_ANN_WAIT);
		break;
	case FIP_ST_VNMP_CLAIM:


		next_time = fip->sol_time + msecs_to_jiffies(FIP_VN_ANN_WAIT);
		if (time_after_eq(jiffies, next_time)) {
			fcoe_ctlr_set_state(fip, FIP_ST_VNMP_UP);
			fcoe_ctlr_vn_send(fip, FIP_SC_VN_BEACON,
					  fcoe_all_vn2vn, 0);
			next_time = jiffies + msecs_to_jiffies(FIP_VN_ANN_WAIT);
			fip->port_ka_time = next_time;
		}
		fcoe_ctlr_vn_disc(fip);
		break;
	case FIP_ST_VNMP_UP:
		next_time = fcoe_ctlr_vn_age(fip);
		if (time_after_eq(jiffies, fip->port_ka_time)) {
			fcoe_ctlr_vn_send(fip, FIP_SC_VN_BEACON,
					  fcoe_all_vn2vn, 0);
			fip->port_ka_time = jiffies +
				 msecs_to_jiffies(FIP_VN_BEACON_INT +
					(prandom_u32() % FIP_VN_BEACON_FUZZ));
		}
		if (time_before(fip->port_ka_time, next_time))
			next_time = fip->port_ka_time;
		break;
	case FIP_ST_LINK_WAIT:
		goto unlock;
	default:
		WARN(1, "unexpected state %d\n", fip->state);
		goto unlock;
	}
	mod_timer(&fip->timer, next_time);
unlock:
	mutex_unlock(&fip->ctlr_mutex);


	if (new_port_id)
		fc_lport_set_local_id(fip->lp, new_port_id);
}
