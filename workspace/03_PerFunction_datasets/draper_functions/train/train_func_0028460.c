drawScene ()
{


    double aspect = (double) gameGLView->width () / gameGLView->height ();
    float fieldHeight = -cubeCentreZ * 2.0 * tan (3.14159 * viewAngle/360.0);
    float fieldWidth  = aspect * fieldHeight;

    foreach (CubeView * v, cubeViews) {
	if (v->sceneID != currentSceneID)
	    continue;

	v->position [X] = v->relX * fieldWidth;
	v->position [Y] = v->relY * fieldHeight;
	v->position [Z] = cubeCentreZ;

	gameGLView->pushGLMatrix ();
	gameGLView->moveGLView (v->position[X],
				v->position[Y],
				v->position[Z]);
	v->cubieSize = v->size / nMax;


	gameGLView->rotateGLView (v->turn, 0.0, 1.0, 0.0);
	gameGLView->rotateGLView (v->tilt, 1.0, 0.0, -1.0);


	glGetDoublev (GL_MODELVIEW_MATRIX, v->matrix0);


	if (v->rotates) {
	    if (demoPhase) {

		tumble();
	    }
	    else {

		moveTracker->usersRotation();
	    }
	}


	glGetDoublev (GL_MODELVIEW_MATRIX, v->matrix);

	cube->drawCube (gameGLView, v->cubieSize);

	gameGLView->popGLMatrix ();
    }


    demoL->   drawLabel (gameGLView);
    frontVL-> drawLabel (gameGLView);
    backVL->  drawLabel (gameGLView);
}
