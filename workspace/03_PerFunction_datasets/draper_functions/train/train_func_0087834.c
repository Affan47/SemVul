runAction( const Context& context )
{
   for ( ViewState::iterator i = newState.begin(); i != newState.end(); ++i  ) {
      MapField* fld = getMap()->getField( i->first );
      oldState[i->first] = fld->visible;
      fld->visible = newState[i->first];
   }
   return ActionResult(0);
}
