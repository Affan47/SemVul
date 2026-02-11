TaskManager( GameMap* map ) : ASC_PG_Dialog( NULL, PG_Rect( -1, -1, 600, 550 ), "Manage Tasks" ), gamemap( map )
      {
         StandardButtonDirection( Horizontal );
         AddStandardButton("Close")->sigClick.connect( SigC::slot( *this, &TaskManager::ok ));
         AddStandardButton("Run All")->sigClick.connect( SigC::slot( *this, &TaskManager::run ));
         selection = new ItemSelectorWidget( this, PG_Rect( 5, 20, Width()-10, Height() - 70 ), new TaskFactory( map ));
      }
