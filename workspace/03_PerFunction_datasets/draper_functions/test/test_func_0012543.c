GrowVMons()
{
	if(!Globals->LAIR_MONSTERS_EXIST) return;

	forlist(&regions) {
		ARegion *r = (ARegion *)elem;
		forlist(&r->objects) {
			Object *obj = (Object *)elem;
			if(obj->type != O_BKEEP) continue;
			forlist(&obj->units) {
				Unit *u = (Unit *)elem;
				int men = u->GetMen(I_BALROG) + 2;
				if(men > 200) men = 200;
				u->items.SetNum(I_BALROG, men);
			}
		}
	}
}
