handleMotion(PG_Point const &p) {
	MenuItem  *item = 0;
	PG_Rect    itemRect;

	if (current != stop) {
		item = *current;
		item->measureItem(&itemRect, true);
	} else
		return false;

	if (item && itemRect.IsInside(p)) {
		if (!selectItem(item, current))
			return false;
	} else
		for (MII i = start; i != stop; i++) {
			item = *i;
			item->measureItem(&itemRect, true);
			itemRect.my_xpos += my_xpos;
			itemRect.my_ypos += my_ypos;

			if (itemRect.IsInside(p)) {
				if (!selectItem(item, i))
					return false;
				break;
			}
		}

	return true;
}
