init( MapField* fld )
{
   this->fld = fld;

   xs = 15;


   TransferControlCommand tcc( fld->getContainer() );

   receivers = tcc.getReceivers();

   tdialogbox::init();

   xsize = 250;
   ysize = 110 + receivers.size() * 40;

   if ( fld->vehicle )
      title = "give unit to";
   else if ( fld->building )
      title = "give building to";

   addbutton ( "~O~k", 10, ysize - 30, xsize/2 - 5, ysize - 10 , 0, 1, 1, true );
   addkey ( 1, ct_enter );
   addbutton ( "~C~ancel", xsize/2 + 5, ysize - 30, xsize-10 - 5, ysize - 10 , 0, 1, 2, true );
   addkey ( 2, ct_esc );


   if ( receivers.size() == 1 )
      markedplayer = 0;
   else
      markedplayer = -1;

   status = 0;


   buildgraphics();


   for ( int j = 0; j < receivers.size(); j++ )
      paintplayer( j );

}
