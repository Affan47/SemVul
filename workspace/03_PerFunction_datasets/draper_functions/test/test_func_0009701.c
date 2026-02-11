doAction(SoAction *action)


{
    SbBool	doCenter, doScaleOrient;
    SoState	*state = action->getState();

    doCenter      = (! center.isIgnored() && ! center.isDefault());
    doScaleOrient = (! scaleOrientation.isIgnored() &&
		     ! scaleOrientation.isDefault());


    if (! translation.isIgnored() && ! translation.isDefault())
	SoModelMatrixElement::translateBy(state, this, translation.getValue());

    if (doCenter)
	SoModelMatrixElement::translateBy(state, this, center.getValue());

    if (! rotation.isIgnored() && ! rotation.isDefault())
	SoModelMatrixElement::rotateBy(state, this, rotation.getValue());

    if (! scaleFactor.isIgnored() && ! scaleFactor.isDefault()) {

	if (doScaleOrient)
	    SoModelMatrixElement::rotateBy(state, this,
					   scaleOrientation.getValue());

	SoModelMatrixElement::scaleBy(state, this, scaleFactor.getValue());

	if (doScaleOrient) {
	    SbRotation r = scaleOrientation.getValue();
	    r.invert();
	    SoModelMatrixElement::rotateBy(state, this, r);
	}
    }

    if (doCenter)
	SoModelMatrixElement::translateBy(state, this, -center.getValue());
}
