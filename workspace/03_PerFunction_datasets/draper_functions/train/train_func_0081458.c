EventList( GameMap* gameMap) : ASC_PG_Dialog( NULL, PG_Rect( -1, -1, 600, 400 ), "Edit Events" ) , gamemap ( gameMap )
      {
         int w = 500;
         PG_Button* b = new PG_Button( this, PG_Rect ( w, 40, 90, 25 ), "~N~ew" );
         b->sigClick.connect( SigC::slot( *this, &EventList::ButtonNew ));

         b = new PG_Button( this, PG_Rect ( w, 80, 90, 25 ), "~E~dit" );
         b->sigClick.connect( SigC::slot( *this, &EventList::ButtonEdit ));

         b = new PG_Button( this, PG_Rect ( w, 120, 90, 25 ), "~D~elete" );
         b->sigClick.connect( SigC::slot( *this, &EventList::ButtonDelete ));

         b = new PG_Button( this, PG_Rect ( w, 160, 90, 25 ), "~O~K" );
         b->sigClick.connect( SigC::slot( *this, &EventList::ButtonOK ));


         listbox = new PG_ListBox( this, PG_Rect( 20, 40, w - 30, Height()-50 ));
         listbox->SetTransparency(255);
         updateListbox();
      }
