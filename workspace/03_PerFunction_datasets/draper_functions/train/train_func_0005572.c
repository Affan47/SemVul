drawCubie (GameGLView * gameGLView, float cubieSize,
				Axis axis, int slice, int angle)
{
    float centre     [nAxes];


    LOOP (i, nAxes) {
	centre [i] = ((float) currentCentre [i]) * cubieSize / 2.0;
    }


    int   myAngle = 0;
    if ((angle != 0) && ((slice == WHOLE_CUBE) ||
			 (currentCentre [axis] == slice))) {
	myAngle = angle;
    }


    gameGLView->drawACubie (cubieSize, centre, axis, myAngle);

    float faceCentre [nAxes];
    int   faceNormal [nAxes];


    foreach (Sticker * sticker, stickers) {


	LOOP (j, nAxes) {
	    faceNormal [j] = sticker->currentFaceCentre [j] - currentCentre [j];
	    faceCentre [j] = ((float) sticker->currentFaceCentre [j]) *
					    cubieSize / 2.0;
	}


	gameGLView->drawASticker (cubieSize, (int) sticker->color,
			  sticker->blinking, faceNormal, faceCentre);
    }


    if (myAngle != 0) {
	gameGLView->finishCubie ();
    }
}
