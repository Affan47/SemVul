LoadNewView (G_GNUC_UNUSED xmlNodePtr node)
{
	Window *pWindow = static_cast < Application * > (GetApplication ())->CreateNewWindow (this);
	View *pView = pWindow->GetView ();
	bool result = pView->Load (node);
	if (!result)
		delete pWindow;
	return result;
}
