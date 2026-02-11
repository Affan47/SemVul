aoc_parse_ie(struct ast_aoc_decoded *decoded, unsigned char *data, unsigned int datalen)
{
	enum AOC_IE ie_id;
	unsigned int len;

	while (datalen >= 2) {
		ie_id = data[0];
		len = data[1];
		if (len > datalen -2) {
			ast_log(LOG_ERROR, "AOC information element length exceeds the total message size\n");
			return -1;
		}

		switch(ie_id) {
		case AOC_IE_CURRENCY:
			if (len == sizeof(struct aoc_ie_currency)) {
				struct aoc_ie_currency ie;
				memcpy(&ie, data + 2, len);
				decoded->currency_amount = ntohl(ie.amount);
				decoded->multiplier = ie.multiplier;
				memcpy(decoded->currency_name, ie.name, sizeof(decoded->currency_name));
			} else {
				ast_log(LOG_WARNING, "Received invalid currency ie\n");
			}
			break;
		case AOC_IE_UNIT:
			if (len == sizeof(struct aoc_ie_unit)) {
				struct aoc_ie_unit ie;
				memcpy(&ie, data + 2, len);
				ast_aoc_add_unit_entry(decoded, ie.valid_amount, ntohl(ie.amount), ie.valid_type, ie.type);
			} else {
				ast_log(LOG_WARNING, "Received invalid unit ie\n");
			}
			break;
		case AOC_IE_BILLING:
			if (len == sizeof(struct aoc_ie_billing)) {
				struct aoc_ie_billing ie;
				memcpy(&ie, data + 2, len);
				decoded->billing_id = ie.id;
			} else {
				ast_log(LOG_WARNING, "Received invalid billing ie\n");
			}
			break;
		case AOC_IE_CHARGING_ASSOCIATION:
			if (len == sizeof(struct aoc_ie_charging_association)) {
				memcpy(&decoded->charging_association, data + 2, sizeof(decoded->charging_association));

				if (decoded->charging_association.charging_type == AST_AOC_CHARGING_ASSOCIATION_ID) {
					decoded->charging_association.charge.id = ntohl(decoded->charging_association.charge.id);
				}
			} else {
				ast_log(LOG_WARNING, "Received invalid charging association ie\n");
			}
			break;
		case AOC_IE_RATE:
			if (len == sizeof(struct aoc_ie_charging_rate)) {
				struct aoc_ie_charging_rate ie;
				memcpy(&ie, data + 2, len);
				aoc_parse_ie_charging_rate(decoded, &ie);
			} else {
				ast_log(LOG_WARNING, "Received invalid charging rate ie\n");
			}
			break;
		case AOC_IE_TERMINATION_REQUEST:
			if (len == 0) {
				decoded->termination_request = 1;
			} else {
				ast_log(LOG_WARNING, "Received invalid termination request ie\n");
			}
			break;
		default:
			ast_log(LOG_WARNING, "Unknown AOC Information Element, ignoring.\n");
		}

		datalen -= (len + 2);
		data += (len + 2);
	}
	return 0;
}
