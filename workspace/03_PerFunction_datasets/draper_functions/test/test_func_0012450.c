setLocalizedContainerName( GameMap* map, const MapCoordinate& pos, const std::string& name )
{
   if ( !map )
      return;

   MapField* fld = map->getField( pos );
   if ( !fld )
      return;

   ContainerBase* c = fld->getContainer();
   if ( !c )
      return;

   if ( !checkModificationConstraints( c ))
      return;

   c->setName( name );
}
