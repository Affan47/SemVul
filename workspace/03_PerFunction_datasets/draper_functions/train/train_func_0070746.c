GetSharedNum(int item)
{
	int count = 0;

	if (ItemDefs[item].type & IT_MAN)
		return items.GetNum(item);

	forlist((&object->region->objects)) {
		Object *obj = (Object *) elem;
		forlist((&obj->units)) {
			Unit *u = (Unit *) elem;
			if ((u->num == num) ||
			(u->faction == faction && u->GetFlag(FLAG_SHARING)))
				count += u->items.GetNum(item);
		}
	}

	return count;
}
