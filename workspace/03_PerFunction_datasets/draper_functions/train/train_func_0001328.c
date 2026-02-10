newScene()
{


	if ( !saveOrCancelDialog() )
		return;


	reinitScene( START_SCENE_RECT );

	mGraphicsView->centerOn( 0 , 0 );
	mGraphicsView->setTransform( QTransform() );


	setWindowFilePath("");
	updateWindowState();
	updateZoomLabel();
	mSceneHasChanged = false;
}
