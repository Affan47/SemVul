slot_newCreature()
{
	Creature * creature = new Creature();
	DataTheme.creatures.getRace( _race )->append( creature );
	slot_lastCreature();
}
