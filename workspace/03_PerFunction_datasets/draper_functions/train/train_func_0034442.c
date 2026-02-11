__ath_regd_init(struct ath_regulatory *reg)
{
	struct country_code_to_enum_rd *country = NULL;
	u16 regdmn;

	if (!reg)
		return -EINVAL;

	ath_regd_sanitize(reg);

	printk(KERN_DEBUG "ath: EEPROM regdomain: 0x%0x\n", reg->current_rd);

	if (!ath_regd_is_eeprom_valid(reg)) {
		pr_err("Invalid EEPROM contents\n");
		return -EINVAL;
	}

	regdmn = ath_regd_get_eepromRD(reg);
	reg->country_code = ath_regd_get_default_country(regdmn);

	if (reg->country_code == CTRY_DEFAULT &&
	    regdmn == CTRY_DEFAULT) {
		printk(KERN_DEBUG "ath: EEPROM indicates default "
		       "country code should be used\n");
		reg->country_code = CTRY_UNITED_STATES;
	}

	if (reg->country_code == CTRY_DEFAULT) {
		country = NULL;
	} else {
		printk(KERN_DEBUG "ath: doing EEPROM country->regdmn "
		       "map search\n");
		country = ath_regd_find_country(reg->country_code);
		if (country == NULL) {
			printk(KERN_DEBUG
				"ath: no valid country maps found for "
				"country code: 0x%0x\n",
				reg->country_code);
			return -EINVAL;
		} else {
			regdmn = country->regDmnEnum;
			printk(KERN_DEBUG "ath: country maps to "
			       "regdmn code: 0x%0x\n",
			       regdmn);
		}
	}

	reg->regpair = ath_get_regpair(regdmn);

	if (!reg->regpair) {
		printk(KERN_DEBUG "ath: "
			"No regulatory domain pair found, cannot continue\n");
		return -EINVAL;
	}

	if (!country)
		country = ath_regd_find_country_by_rd(regdmn);

	if (country) {
		reg->alpha2[0] = country->isoName[0];
		reg->alpha2[1] = country->isoName[1];
	} else {
		reg->alpha2[0] = '0';
		reg->alpha2[1] = '0';
	}

	printk(KERN_DEBUG "ath: Country alpha2 being used: %c%c\n",
		reg->alpha2[0], reg->alpha2[1]);
	printk(KERN_DEBUG "ath: Regpair used: 0x%0x\n",
		reg->regpair->reg_domain);

	return 0;
}
