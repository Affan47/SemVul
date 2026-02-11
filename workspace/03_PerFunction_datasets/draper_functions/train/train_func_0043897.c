onEvent(event::Event* const event) {
	if (event->id() == WantItems::ID) {
		WantItems* e = static_cast<WantItems*> (event);
		for (map<unsigned char, Item>::iterator i = e->items().begin(); i != e->items().end(); ++i) {
			if (i->second.name() == "blindfold" || i->second.name() == "towel") {
				i->second.want(i->second.count());
			}
		}
	} else if (event->id() == GotDiggingTool::ID) {
		_pick_key = (static_cast<GotDiggingTool*> (event))->key();
	}
}
