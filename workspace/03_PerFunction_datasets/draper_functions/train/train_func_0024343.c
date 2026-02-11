runGame ( GameData *game )
{
	if ( game->retVal >= 3 )
		return;

	game->Device = (*game->createExDevice) ( game->deviceParam );
	if ( 0 == game->Device)
	{

		game->retVal = 0;
		return;
	}


	CQuake3EventHandler *eventHandler = new CQuake3EventHandler( game );


	game->load ( "explorer.cfg" );


	for ( u32 i = 0; i < game->CurrentArchiveList.size(); ++i )
	{
		eventHandler->AddArchive ( game->CurrentArchiveList[i] );
	}


	if ( game->CurrentMapName.size () )
	{
		eventHandler->LoadMap ( game->CurrentMapName, 1 );
		if ( 0 == game->loadParam.loadSkyShader )
			eventHandler->AddSky ( 1, "skydome2" );
		eventHandler->CreatePlayers ();
		eventHandler->CreateGUI ();
		eventHandler->SetGUIActive ( 0 );


		if ( game->retVal == 2 )
		{
			eventHandler->GetPlayer( 0 )->setpos ( game->PlayerPosition, game->PlayerRotation );
		}
	}
	else
	{

		eventHandler->AddSky ( 1, "skydome2" );
		eventHandler->CreatePlayers ();
		eventHandler->CreateGUI ();
		eventHandler->SetGUIActive ( 1 );
		background_music ( "IrrlichtTheme.ogg" );
	}


	game->retVal = 3;
	while( game->Device->run() )
	{
		eventHandler->Animate ();
		eventHandler->Render ();

			game->Device->yield();
	}

	game->Device->setGammaRamp ( 1.f, 1.f, 1.f, 0.f, 0.f );
	delete eventHandler;
}
