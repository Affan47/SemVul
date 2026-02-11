doAction(SoAction *action)


{
    SbViewVolume	viewVol;
    SbBool		changeRegion;


    const SbViewportRegion &vpReg =
	SoViewportRegionElement::get(action->getState());


    SoCamera::computeView(vpReg, viewVol, changeRegion);


    SbVec3f dummyJitter;
    setElements(action, viewVol, changeRegion,
		changeRegion ? getViewportBounds(vpReg) : vpReg,
		FALSE, dummyJitter);
}
