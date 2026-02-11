execute( MapDisplayInterface* md )
{
   MapField* fld = gamemap->getField ( pos );
   if ( fld && fld->building )
      fld->building->putResource( res, 0 );
}
