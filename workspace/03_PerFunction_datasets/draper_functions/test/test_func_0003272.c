causeMainWindowRedraw()
{

    dbgprintf("Really redrawing the image\n");


    IOBlackBox->saveGammaParameters(leftX, leftY, rightX, rightY, gammas,
				    RGBmap[0], RGBmap[1], RGBmap[2]);


    IMAGEPARM *p  = (IMAGEPARM *)mainMenuBar->getSelectedItemArgument(IMAGE_LIST_ID);

    if ((p != 0) && (transferRGBEditorPanel != 0)) {

	dbgprintf("Attempting to save the transfer functions parameters\n");
	transferRGBEditorPanel->getParameters(p->Rgamma, p->Ggamma, p->Bgamma,
					      p->Rcontrast, p->Gcontrast, p->Bcontrast,
					      p->Rbrightness, p->Gbrightness, p->Bbrightness);
	dbgprintf("%s got: Rgamma=%g, Rcontrast=%g, Rbrightness=%g\n",
		  p->itempath,
		  p->Rgamma, p->Rcontrast, p->Rbrightness);
    }

    IOBlackBox->applyImageParameters(p, 0, 0, true);
    mainViewer->displayCurrentImage();
    trueRedrawHook();


    redraw();
}
