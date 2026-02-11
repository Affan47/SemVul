onEvent(Event* const event) {
	if (event->id() == ChangedInventoryItems::ID) {
		ChangedInventoryItems* e = static_cast<ChangedInventoryItems*> (event);
		for (set<unsigned char>::iterator k = e->keys().begin(); k != e->keys().end(); ++k) {
			map<unsigned char, Item>::iterator i = Inventory::items().find(*k);
			if (i == Inventory::items().end()) {

				_projectile_slots.erase(*k);
			} else {


				map<const string, const data::Weapon*>::const_iterator w = data::Weapon::weapons().find(i->second.name());
				if (w == data::Weapon::weapons().end())
					continue;
				if (w->second->type() == P_DAGGER || w->second->type() == -P_DART || w->second->type() == P_JAVELIN || w->second->type() == P_KNIFE || w->second->type() == -P_SHURIKEN || w->second->type() == P_SPEAR)
					_projectile_slots.insert(*k);
				else
					_projectile_slots.erase(*k);
			}
		}
	} else if (event->id() == ReceivedItems::ID) {
		ReceivedItems* e = static_cast<ReceivedItems*> (event);
		for (map<unsigned char, Item>::iterator i = e->items().begin(); i != e->items().end(); ++i) {
			map<const string, const data::Weapon*>::const_iterator w = data::Weapon::weapons().find(i->second.name());
			if (w == data::Weapon::weapons().end())
				continue;
			if (w->second->type() == P_DAGGER || w->second->type() == -P_DART || w->second->type() == P_JAVELIN || w->second->type() == P_KNIFE || w->second->type() == -P_SHURIKEN || w->second->type() == P_SPEAR)
				_projectile_slots.insert(i->first);
		}
	}
}
