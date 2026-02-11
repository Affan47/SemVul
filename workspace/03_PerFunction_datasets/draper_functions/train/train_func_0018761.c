actionLists( int id ) const
{
	QList<ActionList*> list;

	for ( int i = 0; i < 32; i++ ) {
		if ( !(id & ( 1 << i )) )
			continue;

		foreach(ActionList* a, d->lists) {
			if ( a->id() & ( 1 << i ) )
				list.append(a);
		}
	}

	return list;
}
