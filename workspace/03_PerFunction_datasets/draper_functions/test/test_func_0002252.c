eval()
{
   if ( !actmap || actmap->actplayer < 0 )
      return;


   MapCoordinate mc = actmap->player[actmap->actplayer].cursorPos;
   MapField* fld = actmap->getField(mc);

   Vehicle* veh = fld? fld->vehicle : NULL;

   BulkGraphicUpdates bgu( this );

   setBargraphValue( "winddisplay", float(actmap->weather.windSpeed ) / 255  );

   setLabelText( "windspeed", actmap->weather.windSpeed );

   if ( fld && mc.valid() && fieldvisiblenow( fld, actmap->getPlayerView() )) {
      setLabelText( "terrain_harbour", fld->bdt.test(cbharbour) ? "YES" : "NO" );
      setLabelText( "terrain_pipe", fld->bdt.test(cbpipeline) || fld->building ? "YES" : "NO" );

      setLabelText( "terrain_defencebonus", fld->getdefensebonus() );
      setLabelText( "terrain_attackbonus", fld->getattackbonus() );
      setLabelText( "terrain_jam", fld->getjamming() );
      setLabelText( "terrain_name", fld->typ->terraintype->name );

      int unitspeed;
      if ( veh )
         unitspeed = getmaxwindspeedforunit ( veh );
      else
         unitspeed = maxint;

       int windspeed = actmap->weather.windSpeed*maxwindspeed ;
       if ( unitspeed < 255*256 ) {
          if ( windspeed > unitspeed*9/10 )
             setBarGraphColor( "winddisplay", 0xff0000  );
          else
             if ( windspeed > unitspeed*66/100 )
                setBarGraphColor( "winddisplay", 0xffff00  );
             else
                setBarGraphColor( "winddisplay", 0x00ff00  );
       } else
          setBarGraphColor( "winddisplay", 0x00ff00  );

   } else {
      setLabelText( "terrain_harbour", "" );
      setLabelText( "terrain_pipe", "" );

      setLabelText( "terrain_defencebonus", "" );
      setLabelText( "terrain_attackbonus", "" );
      setLabelText( "terrain_jam", "" );
      setLabelText( "terrain_name", "" );
      setBarGraphColor( "winddisplay", 0x00ff00  );
   }

   if ( mc.valid() && fld ) {
      if ( veh && fieldvisiblenow( fld, actmap->getPlayerView() ) ) {
         showUnitData( veh, NULL, fld );
      } else {

         Building* bld = fld->building;
         if ( bld && fieldvisiblenow( fld, actmap->getPlayerView() ) )
            showUnitData( NULL, bld, fld );
         else
            showUnitData( NULL, NULL, fld );
      }
   }


}
