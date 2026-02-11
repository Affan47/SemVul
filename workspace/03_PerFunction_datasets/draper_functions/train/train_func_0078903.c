UserStartStrokeP(tdmInteractor I, int x, int y, int btn, int s)
{
    float dx, dy, dz;
    DEFDATA(I,tdmUserInteractorData);
    DEFGLOBALDATA(UDATA(I));
    UserInteractor *imode = ((UserInteractor *)_dxd_UserInteractors) + PDATA(mode);
    DXMouseEvent mouse;

    if (PDATA(mode) < 0 || !(imode->EventHandler))
        return;


    CDATA(xlast) = x;
    CDATA(ylast) = y;

    PDATA(button) = btn;

    _dxfGetViewMatrix(CDATA(stack), CDATA(viewXfm));

    if (imode->SetCamera)
	imode->SetCamera(PDATA(userData),  CDATA(to), CDATA(from), CDATA(up),
				CDATA(projection), CDATA(fov), CDATA(width));
    if (imode->SetRenderable)
	imode->SetRenderable(PDATA(userData), OBJECT);

    switch (PDATA(button))
    {
	case 1: mouse.event = DXEVENT_LEFT;   break;
	case 2: mouse.event = DXEVENT_MIDDLE; break;
	case 3: mouse.event = DXEVENT_RIGHT;  break;
    }

    mouse.x	 = x;
    mouse.y	 = y;
    mouse.state  = BUTTON_DOWN;
    mouse.kstate = s;

    imode->EventHandler(PDATA(userData), (DXEvent *)&mouse);

    dx = CDATA(to)[0] - CDATA(from)[0];
    dy = CDATA(to)[1] - CDATA(from)[1];
    dz = CDATA(to)[2] - CDATA(from)[2];
    CDATA(vdist) = sqrt(dx*dx + dy*dy + dz*dz);

    EXIT((""));
}
