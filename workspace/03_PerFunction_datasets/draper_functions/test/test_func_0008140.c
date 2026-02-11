setElements(SoAction *action, SbViewVolume &viewVol,
		      SbBool setRegion, const SbViewportRegion &vpReg,
		      SbBool doJitter, const SbVec3f &jitterAmount)


{
    SoState	*state = action->getState();
    SbMatrix	viewMat, projMat;


    viewVol.getMatrices(viewMat, projMat);


    if (doJitter) {
	SbMatrix m;
	m.setTranslate(jitterAmount);
	projMat.multRight(m);
    }


    SoProjectionMatrixElement::set(state, this, projMat);


    if (setRegion)
	SoViewportRegionElement::set(state, vpReg);


    SbBool modelIsIdent;
    const SbMatrix &modelMat = SoModelMatrixElement::get(state, modelIsIdent);
    if (! modelIsIdent) {
	viewMat.multRight(modelMat.inverse());


	viewVol.transform(modelMat);
    }

    SoViewVolumeElement::set(state, this, viewVol);
    SoViewingMatrixElement::set(state, this, viewMat);
}
