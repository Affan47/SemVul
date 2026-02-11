actionList( QString name ) const
{
	foreach(ActionList* a, d->lists) {
		if (a->name() == name)
			return a;
	}

	return 0;
}
