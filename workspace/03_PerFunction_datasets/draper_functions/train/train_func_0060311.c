carl9170_handle_ps(struct ar9170 *ar, struct carl9170_rsp *rsp)
{
	u32 ps;
	bool new_ps;

	ps = le32_to_cpu(rsp->psm.state);

	new_ps = (ps & CARL9170_PSM_COUNTER) != CARL9170_PSM_WAKE;
	if (ar->ps.state != new_ps) {
		if (!new_ps) {
			ar->ps.sleep_ms = jiffies_to_msecs(jiffies -
				ar->ps.last_action);
		}

		ar->ps.last_action = jiffies;

		ar->ps.state = new_ps;
	}
}
