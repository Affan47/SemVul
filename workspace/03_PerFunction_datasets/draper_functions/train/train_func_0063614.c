removeMapCreature( GenericMapCreature * creature )
{
	if( creature ) {
		_creatures.removeAll( creature );
		delete creature;
	}
}
