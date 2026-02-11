attack( Vehicle* veh, const MapCoordinate& target )
{
   auto_ptr<AttackCommand> muc ( new AttackCommand( veh ));
   muc->setTarget( target );
   ActionResult res = muc->execute( createTestingContext( veh->getMap() ));
   if ( res.successful() )
      muc.release();
   else
      throw ActionResult(res);
}
