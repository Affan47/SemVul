setUpConnections( SbBool onOff, SbBool doItAlways )
{
    if ( !doItAlways && connectionsSetUp == onOff)
	return onOff;

    if ( onOff ) {


	SoDragger::setUpConnections( onOff, FALSE );


	SoDragger *trD = (SoDragger *) getAnyPart( "translator", FALSE );
	if (trD != NULL) {


	    SoNode *n;
	    n = SoNode::getByName("directionalLightTranslatorLineTranslator");
	    trD->setPartAsDefault("xTranslator.translator", n );
	    trD->setPartAsDefault("yTranslator.translator", n );
	    trD->setPartAsDefault("zTranslator.translator", n );

	    n = SoNode::getByName(
			    "directionalLightTranslatorLineTranslatorActive");
	    trD->setPartAsDefault("xTranslator.translatorActive", n );
	    trD->setPartAsDefault("yTranslator.translatorActive", n );
	    trD->setPartAsDefault("zTranslator.translatorActive", n );

	    n = SoNode::getByName("directionalLightTranslatorPlaneTranslator");
	    trD->setPartAsDefault("yzTranslator.translator", n );
	    trD->setPartAsDefault("xzTranslator.translator", n );
	    trD->setPartAsDefault("xyTranslator.translator", n );

	    n = SoNode::getByName(
			    "directionalLightTranslatorPlaneTranslatorActive");
	    trD->setPartAsDefault("yzTranslator.translatorActive", n );
	    trD->setPartAsDefault("xzTranslator.translatorActive", n );
	    trD->setPartAsDefault("xyTranslator.translatorActive", n );

	    registerChildDragger( trD );
	}

	SoRotateSphericalDragger *roD
	    = (SoRotateSphericalDragger *) getAnyPart( "rotator", FALSE );
	if (roD != NULL) {


	    SbSphereSectionProjector *ssp = new SbSphereSectionProjector();
	    ssp->setRadialFactor( 1.0 );
	    roD->setProjector(ssp);


	    roD->setPartAsDefault("rotator",
			    "directionalLightRotatorRotator");
	    roD->setPartAsDefault("rotatorActive",
			    "directionalLightRotatorRotatorActive");
	    roD->setPartAsDefault("feedback",
			    "directionalLightRotatorFeedback" );
	    roD->setPartAsDefault("feedbackActive",
			  "directionalLightRotatorFeedbackActive");

	    registerChildDragger( roD );

	}


	fieldSensorCB( this, NULL );


	if (rotFieldSensor->getAttachedField() != &rotation)
	    rotFieldSensor->attach( &rotation );
	if (translFieldSensor->getAttachedField() != &translation)
	    translFieldSensor->attach( &translation );
    }
    else {


        SoDragger *trD = (SoDragger *) getAnyPart( "translator", FALSE );
	if (trD)
        unregisterChildDragger( trD );

        SoDragger *roD = (SoDragger *) getAnyPart( "rotator", FALSE );
	if (roD)
        unregisterChildDragger( roD );


	if (rotFieldSensor->getAttachedField())
	    rotFieldSensor->detach();
	if (translFieldSensor->getAttachedField())
	    translFieldSensor->detach();

	SoDragger::setUpConnections( onOff, FALSE );
    }

    return !(connectionsSetUp = onOff);
}
