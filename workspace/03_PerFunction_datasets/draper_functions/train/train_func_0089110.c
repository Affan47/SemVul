__regulatory_hint(struct ieee80211_dev_regulatory *reg,
			     struct regulatory_request *pending_request)
{
	bool intersect = false;
	int r = 0;

	r = ignore_request(reg, pending_request);

	if (r == REG_INTERSECT) {
		if (pending_request->initiator ==
		    IEEE80211_REGDOM_SET_BY_DRIVER) {
			r = reg_copy_regd(&reg->regd, regcore->regd);
			if (r) {
				free(pending_request);
				return r;
			}
		}
		intersect = true;
	} else if (r) {


		if (r == -EALREADY &&
		    pending_request->initiator ==
		    IEEE80211_REGDOM_SET_BY_DRIVER) {
			r = reg_copy_regd(&reg->regd, regcore->regd);
			if (r) {
				free(pending_request);
				return r;
			}
			r = -EALREADY;
			goto new_request;
		}
		free(pending_request);
		return r;
	}

new_request:
	if (regcore->last_request != &core_request_world)
		free(regcore->last_request);

	regcore->last_request = pending_request;
	regcore->last_request->intersect = intersect;

	pending_request = NULL;

	if (regcore->last_request->initiator == IEEE80211_REGDOM_SET_BY_USER) {
		regcore->user_alpha2[0] = regcore->last_request->alpha2[0];
		regcore->user_alpha2[1] = regcore->last_request->alpha2[1];
	}


	if (r < 0) {


		if (r == -EALREADY) {
			regcore->ops->send_reg_change_event(regcore->last_request);
			reg_set_request_processed();
		}
		return r;
	}

	return regcore->ops->call_crda(regcore->last_request->alpha2);
}
