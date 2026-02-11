respawn ()
{
	if (!Device)
		return;
	ICameraSceneNode* camera = Device->getSceneManager()->getActiveCamera();

	Device->getLogger()->log( "respawn" );

	if ( StartPositionCurrent >= Q3StartPosition (
			Mesh, camera,StartPositionCurrent++,
			cam ()->getEllipsoidTranslation() )
		)
	{
		StartPositionCurrent = 0;
	}
}
