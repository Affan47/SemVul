registerChilds( CargoDialog* cd ) {
         SubWindow::registerChilds( cd );

         if ( widget ) {
            PG_Button* b = dynamic_cast<PG_Button*>( widget->FindChild( "RepairButton", true ) );
            if ( b )
               b->sigClick.connect( SigC::slot( *this, &BuildingControlWindow::repair ));
         }
      }
