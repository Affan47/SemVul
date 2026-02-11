redrawContours()
{
	gboolean reBuildFirstPlaneContours = TRUE;
	gint  i;

	if(newContours && nPlanesContours>0)
	{
		if(nPlanesContours==1 && !animateContours ) showColorMapContours();
		else hideColorMapContours();

		if(newPlaneGridForContours)
		{


	   		contoursLists[nPlanesContours-1]= ContoursGenLists(contoursLists[nPlanesContours-1],gridPlaneForContours,numberOfContours,values,i0Contours,i1Contours,numPlaneContours,gapContours);
			addContoursPovRay(gridPlaneForContours,numberOfContours,values,i0Contours,i1Contours,numPlaneContours,gapContours);

			newPlaneGridForContours = FALSE;

			if(nPlanesContours!=1)
			{
				if(gridPlaneForContours) g_free(gridPlaneForContours);
				gridPlaneForContours = NULL;
			}

		}
		else
		{
	   		contoursLists[nPlanesContours-1]= ContoursGenLists(contoursLists[nPlanesContours-1],grid,numberOfContours,values,i0Contours,i1Contours,numPlaneContours,gapContours);
	   		addContoursPovRay(grid,numberOfContours,values,i0Contours,i1Contours,numPlaneContours,gapContours);
		}
		newContours = FALSE;
		reBuildFirstPlaneContours = FALSE;

	}
	if(nPlanesContours>1 && gridPlaneForContours)
	{
		if(gridPlaneForContours) g_free(gridPlaneForContours);
		gridPlaneForContours = NULL;
	}
	if(reBuildFirstPlaneContours && nPlanesContours==1 && BeginX == -1 )
	{
		deleteContoursPovRayFile();
		if(gridPlaneForContours && reDrawContoursPlane)
		{
	   		contoursLists[nPlanesContours-1]= ContoursGenLists(contoursLists[nPlanesContours-1],gridPlaneForContours,numberOfContours,values,i0Contours,i1Contours,numPlaneContours,gapContours);
			addContoursPovRay(gridPlaneForContours,numberOfContours,values,i0Contours,i1Contours,numPlaneContours,gapContours);
		}
		else
		if(reDrawContoursPlane)
		{
	   		contoursLists[nPlanesContours-1]= ContoursGenLists(contoursLists[nPlanesContours-1],grid,numberOfContours,values,i0Contours,i1Contours,numPlaneContours,gapContours);
	   		addContoursPovRay(grid,numberOfContours,values,i0Contours,i1Contours,numPlaneContours,gapContours);
		}
	}

	for(i=0;i<nPlanesContours;i++) ContoursShowLists(contoursLists[i]);
}
