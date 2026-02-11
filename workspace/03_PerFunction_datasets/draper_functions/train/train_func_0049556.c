scoreDigger(const Item& item) {
	if (data::Pickaxe::pickaxes().find(item.name()) == data::Pickaxe::pickaxes().end() || item.beatitude() == CURSED)
		return -1;
	int score = 1;
	if (item.beatitude() != BEATITUDE_UNKNOWN)
		score += 2;

	if (item.name() == "pick-axe")
		score++;
	else if (Inventory::keyForSlot(SLOT_SHIELD))
		score = -1;
	return score;
}
