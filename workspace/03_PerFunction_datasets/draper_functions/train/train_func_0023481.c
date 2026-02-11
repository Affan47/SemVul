analyze() {
	if (_lamp_key == ILLEGAL_ITEM || Saiph::encumbrance() >= OVERTAXED)
		return;

	map<unsigned char, Item>::iterator l = Inventory::items().find(_lamp_key);
	if (l != Inventory::items().end() && l->second.additional() == "")
		World::setAction(new action::Apply(this, _lamp_key, 100, false));
}
