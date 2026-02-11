handleMouseEvent (MouseEvent event, int button, int mX, int mY)
{

    if (demoPhase) {
	if (event == ButtonUp) {
	    stopDemo ();
	    restoreState ();
	    mainWindow->describePuzzle (option [optXDim], option [optYDim],
				option [optZDim], option [optShuffleMoves]);
	}
	return;
    }

    if (tooBusy())
	return;

    if (((event == ButtonDown) && (moveFeedback != None)) ||
	((event == ButtonUp) && (moveFeedback != Mouse))) {

	return;
    }


    if (event == ButtonDown) {
	moveFeedback = Mouse;
	time.start();
	gameGLView->setBlinkIntensity (1.0);
    }
    else {
	moveFeedback = None;
    }


    moveTracker->mouseInput (currentSceneID, cubeViews, cube,
			event, button, mX, mY);
}
