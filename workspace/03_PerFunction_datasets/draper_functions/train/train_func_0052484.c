updateLimitBoxAndFeedback()


{


    ref();

    if ( xFeedback.getValue() != oldXAxisNode ||
	 yFeedback.getValue() != oldYAxisNode ||
	 zFeedback.getValue() != oldZAxisNode ) {

	oldXAxisNode = SO_GET_ANY_PART(this,"xFeedback",SoSeparator);
	oldYAxisNode = SO_GET_ANY_PART(this,"yFeedback",SoSeparator);
	oldZAxisNode = SO_GET_ANY_PART(this,"zFeedback",SoSeparator);


	static SoGetBoundingBoxAction *bba = NULL;
	if (bba == NULL)
	    bba = new SoGetBoundingBoxAction(getViewportRegion());
	else
	    bba->setViewportRegion(getViewportRegion());

	float   xMin, yMin, zMin, xMax, yMax, zMax;
	SbVec3f min, max;

	bba->apply(xFeedback.getValue());
	bba->getBoundingBox().getBounds( xMin, yMin, zMin, xMax, yMax, zMax );
	min[0] = xMin;
	max[0] = xMax;

	bba->apply(yFeedback.getValue());
	bba->getBoundingBox().getBounds( xMin, yMin, zMin, xMax, yMax, zMax );
	min[1] = yMin;
	max[1] = yMax;

	bba->apply(zFeedback.getValue());
	bba->getBoundingBox().getBounds( xMin, yMin, zMin, xMax, yMax, zMax );
	min[2] = zMin;
	max[2] = zMax;


	SbVec3f newDiag = (max - min) / 2.0;


	for (int i = 0; i < 3; i++) {
	    if (newDiag[i] <= getMinScale())
		newDiag[i] = 1.0;
	}

	SbVec3f oldDiag = limitBox.getMax() -
			  limitBox.getCenter();


	if ( newDiag != oldDiag ) {


	    SbMatrix localToWorld = getLocalToWorldMatrix();

	    SbVec3f zeroPt(0,0,0);
	    localToWorld.multVecMatrix( zeroPt, zeroPt );

	    limitBox.setBounds(zeroPt - newDiag, zeroPt + newDiag );
	}
    }

    setFeedbackGeometry();


    unrefNoDelete();
}
