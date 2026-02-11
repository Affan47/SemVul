node_state_string(uint16_t inx)
{
	int  base            = (inx & NODE_STATE_BASE);
	bool comp_flag       = (inx & NODE_STATE_COMPLETING);
	bool drain_flag      = (inx & NODE_STATE_DRAIN);
	bool fail_flag       = (inx & NODE_STATE_FAIL);
	bool maint_flag      = (inx & NODE_STATE_MAINT);
	bool resume_flag     = (inx & NODE_RESUME);
	bool no_resp_flag    = (inx & NODE_STATE_NO_RESPOND);
	bool power_down_flag = (inx & NODE_STATE_POWER_SAVE);
	bool power_up_flag   = (inx & NODE_STATE_POWER_UP);

	if (maint_flag) {
		if (no_resp_flag)
			return "MAINT*";
		if (base != NODE_STATE_ALLOCATED)
			return "MAINT";
	}
	if (drain_flag) {
		if (comp_flag || (base == NODE_STATE_ALLOCATED)) {
			if (no_resp_flag)
				return "DRAINING*";
			return "DRAINING";
		} else if (base == NODE_STATE_ERROR) {
			if (no_resp_flag)
				return "ERROR*";
			return "ERROR";
		} else if (base == NODE_STATE_MIXED) {
			if (no_resp_flag)
				return "MIXED*";
			return "MIXED";
		} else {
			if (no_resp_flag)
				return "DRAINED*";
			return "DRAINED";
		}
	}
	if (fail_flag) {
		if (comp_flag || (base == NODE_STATE_ALLOCATED)) {
			if (no_resp_flag)
				return "FAILING*";
			return "FAILING";
		} else {
			if (no_resp_flag)
				return "FAIL*";
			return "FAIL";
		}
	}

	if (inx == NODE_STATE_POWER_SAVE)
		return "POWER_DOWN";
	if (inx == NODE_STATE_POWER_UP)
		return "POWER_UP";
	if (base == NODE_STATE_DOWN) {
		if (no_resp_flag)
			return "DOWN*";
		return "DOWN";
	}

	if (base == NODE_STATE_ALLOCATED) {
		if (power_up_flag)
			return "ALLOCATED#";
		if (power_down_flag)
			return "ALLOCATED~";
		if (no_resp_flag)
			return "ALLOCATED*";
		if (comp_flag)
			return "ALLOCATED+";
		return "ALLOCATED";
	}
	if (comp_flag) {
		if (no_resp_flag)
			return "COMPLETING*";
		return "COMPLETING";
	}
	if (base == NODE_STATE_IDLE) {
		if (power_up_flag)
			return "IDLE#";
		if (power_down_flag)
			return "IDLE~";
		if (no_resp_flag)
			return "IDLE*";
		return "IDLE";
	}
	if (base == NODE_STATE_ERROR) {
		if (power_up_flag)
			return "ERROR#";
		if (power_down_flag)
			return "ERROR~";
		if (no_resp_flag)
			return "ERROR*";
		return "ERROR";
	}
	if (base == NODE_STATE_MIXED) {
		if (power_up_flag)
			return "MIXED#";
		if (power_down_flag)
			return "MIXED~";
		if (no_resp_flag)
			return "MIXED*";
		return "MIXED";
	}
	if (base == NODE_STATE_FUTURE) {
		if (no_resp_flag)
			return "FUTURE*";
		return "FUTURE";
	}
	if (resume_flag)
		return "RESUME";
	if (base == NODE_STATE_UNKNOWN) {
		if (no_resp_flag)
			return "UNKNOWN*";
		return "UNKNOWN";
	}
	return "?";
}
