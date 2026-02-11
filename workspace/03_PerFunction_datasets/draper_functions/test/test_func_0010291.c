showSmallIcons( PG_Widget* parent, const SPoint& pos, bool cursorChanged )
{
   clearSmallIcons();

   BulkGraphicUpdates bgu;

   SmallGuiButton* firstSmallButton = NULL;

   int count = 0;
   if ( !cursorChanged || CGameOptions::Instance()->mouse.singleClickAction ) {
      for ( int j = 0; j < buttons.size(); ++j)
         if ( !getButton(j)->IsHidden() )
            ++count;

      if ( count ) {
         if ( !smallButtonHolder )
            smallButtonHolder = new SmallButtonHolder ( NULL, PG_Rect::null );


         smallButtonHolder->MoveWidget( PG_Rect( pos.x, pos.y, count * smallGuiIconSizeX + (count-1)*smallGuiIconSpace, smallGuiIconSizeY ), false );

         for ( int j = 0; j < buttons.size(); ++j) {
            GuiButton* b = getButton(j);
            if ( !b->IsHidden() ) {
               SmallGuiButton* sgi = getSmallButton( j );
               sgi->updateIcon();
               sgi->SetHidden(false);
               if ( j == 0  && sgi->IsMouseInside() )
                  firstSmallButton = sgi;
            } else
               getSmallButton( j )->SetHidden(true);
         }
      }
   }

   bgu.release();
   if ( smallButtonHolder && count ) {
      smallButtonHolder->BringToFront();
      smallButtonHolder->Show();
      smallButtonHolder->Lock();

      if ( firstSmallButton ) {
         firstSmallButton->press();
         firstSmallButton->showInfoText();
      }
   }

   return true;
}
