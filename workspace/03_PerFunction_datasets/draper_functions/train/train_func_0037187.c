listBindings(BindingList & list,
	KeySequence const & prefix, KeyMap::ItemType tag) const
{
	Table::const_iterator it = table.begin();
	Table::const_iterator it_end = table.end();
	for (; it != it_end; ++it) {

		if (it->prefixes.get()) {
			KeySequence seq = prefix;
			seq.addkey(it->code, it->mod.first);
			it->prefixes->listBindings(list, seq, tag);
		} else {
			KeySequence seq = prefix;
			seq.addkey(it->code, it->mod.first);
			list.push_back(Binding(it->func, seq, tag));
		}
	}
}


}
