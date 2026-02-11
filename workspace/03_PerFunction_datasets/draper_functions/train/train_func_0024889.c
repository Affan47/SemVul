GetSpoils(AList * losers, ItemList *spoils, int ass)
{
	ItemList *ships = new ItemList;
	forlist(losers) {
		Unit * u = ((Location *) elem)->unit;
		int numalive = u->GetSoldiers();
		int numdead = u->losses;
		forlist(&u->items) {
			Item * i = (Item *) elem;
			if(IsSoldier(i->type)) continue;

			if(ItemDefs[i->type].type & IT_SHIP) continue;


			if((ass == 2) && (i->type == I_AMULETOFTS)) continue;
			float percent = (float)numdead/(float)(numalive+numdead);

			if(ItemDefs[i->type].type & IT_SHIP) {
				if(getrandom(100) < percent) {
					u->items.SetNum(i->type, 0);
					if(i->num < ships->GetNum(i->type))
						ships->SetNum(i->type, i->num);
				}
			} else {
				int num = (int)(i->num * percent);
				int num2 = (num + getrandom(2))/2;
				spoils->SetNum(i->type, spoils->GetNum(i->type) + num2);
				u->items.SetNum(i->type, i->num - num);
			}
		}
	}

	for(int sh = 0; sh < NITEMS; sh++) {
		if(ItemDefs[sh].type & IT_SHIP) {
			spoils->SetNum(sh, ships->GetNum(sh));
		}
	}
}
