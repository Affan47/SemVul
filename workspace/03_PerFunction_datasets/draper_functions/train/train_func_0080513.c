write(SoWriteAction *action)


{
    SbBool 		save = rotation.isConnectionEnabled();
    SoEngineOutput	*rotationSource;


    if (rotation.isConnected() &&
	rotation.getConnectedEngine(rotationSource) &&
	rotationSource == internalConnection) {

	rotation.enableConnection(FALSE);
    }

    SoRotation::write(action);

    rotation.enableConnection(save);
}
