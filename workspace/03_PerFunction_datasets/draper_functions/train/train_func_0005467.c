selectWish(bool wish_from_wand) {
	_last_wish_call.clear();
	if (wish_from_wand && charging_key == ILLEGAL_ITEM) {
		_last_wish_call = "scroll of charging";
		return "3 scrolls of charging";
	}
	bool have_mr = (have("cloak of magic resistance") || have("gray dragon scale") || have("Magicbane"));
	bool reflect = (have("amulet of reflection") || have("shield of reflection") || have("silver shield") || have("silver dragon scale"));

	if (wish_from_wand && !have_mr && !reflect)
		return "silver dragon scale mail";

	if (!have_mr) {
		if (have("silver dragon scale"))
			return _last_wish_call = "cloak of magic resistance";
		return "gray dragon scale mail";
	} else if (!reflect) {
		if (have("gray dragon scale"))
			return _last_wish_call = "amulet of reflection";
		return "silver dragon scale mail";
	} else if (!have("speed boots")) {
		return _last_wish_call = "pair of speed boots";
	} else if (!have("gauntlets of power")) {
		return _last_wish_call = "pair of gauntlets of power";
	}

	if (!have("amulet of reflection"))
		return _last_wish_call = "amulet of life saving";
	_last_wish_call = "potion of full healing";
	return "3 potions of full healing";
}
