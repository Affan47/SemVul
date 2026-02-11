CSceneNodeAnimatorCameraMaya(gui::ICursorControl* cursor, f32 rotate, f32 zoom, f32 translate)
	: CursorControl(cursor), Zooming(false), Rotating(false), Moving(false),
	Translating(false), ZoomSpeed(zoom), RotateSpeed(rotate), TranslateSpeed(translate),
	CurrentZoom(70.0f), RotX(0.0f), RotY(0.0f), OldCamera(0), MousePos(0.5f, 0.5f)
{
	#ifdef _DEBUG
	setDebugName("CSceneNodeAnimatorCameraMaya");
	#endif

	if (CursorControl)
	{
		CursorControl->grab();
		MousePos = CursorControl->getRelativePosition();
	}

	allKeysUp();
}
