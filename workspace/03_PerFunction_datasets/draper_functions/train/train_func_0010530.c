validateMatrices()


{


    if ( cachedPathToThisValid && cachedMotionMatrixValid )
	return;


    if ( cachedPathToThisValid == FALSE ) {


	SoPath *pathToMe = createPathToThis();
	if ( pathToMe != NULL ) {
	    pathToMe->ref();
	    static SoGetMatrixAction *ma = NULL;
	    if (ma == NULL)
		ma = new SoGetMatrixAction( getViewportRegion() );
	    else
		ma->setViewportRegion( getViewportRegion() );

	    ma->apply( pathToMe );
	    preMotionToWorldMatrix = ma->getMatrix();
	    worldToPreMotionMatrix = ma->getInverse();
	    pathToMe->unref();
	}
	else {
	    preMotionToWorldMatrix.makeIdentity();
	    worldToPreMotionMatrix.makeIdentity();
	}
    }


    if ( cachedMotionMatrixValid == FALSE ) {
	cachedMotionMatrix = getMotionMatrix();
    }


    postMotionToWorldMatrix = preMotionToWorldMatrix;
    postMotionToWorldMatrix.multLeft( cachedMotionMatrix );

    worldToPostMotionMatrix = worldToPreMotionMatrix;
    worldToPostMotionMatrix.multRight( cachedMotionMatrix.inverse() );

    cachedMotionMatrixValid = TRUE;
    cachedPathToThisValid = TRUE;
}
