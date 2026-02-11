viewUnitSetinfo ( void )
{
   ASCString s;
   MapField* fld = actmap->getField( actmap->getCursor() );
   if ( fld && fieldvisiblenow  ( fld ) && fld->vehicle ) {

         s += "#fontsize=18#Unit Information:#fontsize=14##aeinzug20##eeinzug20##crtp20#" ;

         const VehicleType* typ = fld->vehicle->typ;


         s += "Unit name: " ;
         if ( !typ->name.empty() )
            s += typ->name ;
         else
            s += typ->description;

         s += "\nUnit owner: " + ASCString::toString( fld->vehicle->getOwner() ) + " - " + actmap->getPlayer(fld->vehicle).getName();

         s += "\nUnit ID: " + ASCString::toString( typ->id );

         if ( !typ->location.empty() )
            s += typ->location;

         if ( unitSets.size() > 0 )
            for ( unsigned int i = 0; i < unitSets.size(); i++ )
               if ( unitSets[i]->isMember ( typ->id,SingleUnitSet::unit )) {
                  s += "Unit is part of this unit set:";
                  if ( unitSets[i]->name.length()) {
                     s += "#aeinzug20##eeinzug20#\nName: #aeinzug60##eeinzug60#\n";
                     s += unitSets[i]->name;
                  }
                  if ( unitSets[i]->maintainer.length()) {
                     s += "#aeinzug20##eeinzug20#\nMaintainer: #aeinzug60##eeinzug60#\n";
                     s += unitSets[i]->maintainer;
                  }
                  if ( unitSets[i]->information.length()) {
                     s += "#aeinzug20##eeinzug20#\nInformation: #aeinzug60##eeinzug60#\n";
                     s += unitSets[i]->information;
                  }
                  s += "#aeinzug0##eeinzug0#\n";
               }


   } else
      s += "\nNo unit selected";

   ViewFormattedText vft( "Unit information", s, PG_Rect( -1, -1, 400, 350) );
   vft.Show();
   vft.RunModal();
}
