updateScaleInfo(scene::ISceneNode* model)
{
	IGUIElement* toolboxWnd = Device->getGUIEnvironment()->getRootGUIElement()->getElementFromId(GUI_ID_DIALOG_ROOT_WINDOW, true);
	if (!toolboxWnd)
		return;
	if (!model)
	{
		toolboxWnd->getElementFromId(GUI_ID_X_SCALE, true)->setText( L"-" );
		toolboxWnd->getElementFromId(GUI_ID_Y_SCALE, true)->setText( L"-" );
		toolboxWnd->getElementFromId(GUI_ID_Z_SCALE, true)->setText( L"-" );
	}
	else
	{
		core::vector3df scale = model->getScale();
		toolboxWnd->getElementFromId(GUI_ID_X_SCALE, true)->setText( core::stringw(scale.X).c_str() );
		toolboxWnd->getElementFromId(GUI_ID_Y_SCALE, true)->setText( core::stringw(scale.Y).c_str() );
		toolboxWnd->getElementFromId(GUI_ID_Z_SCALE, true)->setText( core::stringw(scale.Z).c_str() );
	}
}
