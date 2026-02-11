MoveUnitCommand( GameMap* map ) : UnitCommand( map )
{
   map->sigCoordinateShift.connect( SigC::slot( *this, &MoveUnitCommand::changeCoordinates ));
}
