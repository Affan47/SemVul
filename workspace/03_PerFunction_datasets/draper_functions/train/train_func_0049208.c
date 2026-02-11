CheckFleets()
{
	forlist(&objects) {
		Object *o = (Object *) elem;
		if(o->type == O_FLEET) {
			int bail = 0;
			if (o->FleetCapacity() < 1) bail = 1;
			int alive = 0;
			forlist(&o->units) {
				Unit * unit = (Unit *) elem;
				if(unit->IsAlive()) alive = 1;
				if(bail > 0) unit->MoveUnit(GetDummy());
			}


			if(TerrainDefs[type].similar_type == R_OCEAN) alive = 1;
			if((alive == 0) || (bail == 1)) {
				objects.Remove(o);
				delete o;
			}
		}
	}
}
