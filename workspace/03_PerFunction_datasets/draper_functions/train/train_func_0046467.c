PlayerSetupWindow( GameMap* actmap, bool allEditable, PG_Widget *parent, const PG_Rect &r ) : ASC_PG_Dialog( parent, r, "Players" )
      {
         asw = new PlayerSetupWidget( actmap, PlayerSetupWidget::AllEditable, this, PG_Rect( 5, 30, r.Width() - 10, r.Height() - 60 ));
         PG_Button* ok = new PG_Button( this, PG_Rect( Width() - 200, Height() - 30, 90, 20 ), "OK" );
         ok->sigClick.connect( SigC::slot( *this, &PlayerSetupWindow::Apply ));
         PG_Button* cancel = new PG_Button( this, PG_Rect( Width() - 100, Height() - 30, 90, 20 ), "Cancel" );
         cancel->sigClick.connect( SigC::slot( *this, &PlayerSetupWindow::QuitModal ));
      }
