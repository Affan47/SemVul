DoMouseDown(float frametime)
{
	OwnerSystem->SetActiveObject(this);

	if ( (OwnerSystem->GetMouseX() >= CheckCoords[0])
		&& (OwnerSystem->GetMouseX() <= CheckCoords[2])
		&& (OwnerSystem->GetMouseY() >= CheckCoords[1])
		&& (OwnerSystem->GetMouseY() <= CheckCoords[3]) ) {
		HighlightStatus = 2;
	}

	return OF_TRUE;
}
