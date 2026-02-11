delete_event(GtkWidget * w, GdkEvent * , gpointer )
{
	XAP_UnixFrameImpl * pUnixFrameImpl = static_cast<XAP_UnixFrameImpl *>(g_object_get_data(G_OBJECT(w), "user_data"));
	XAP_Frame* pFrame = pUnixFrameImpl->getFrame();
	XAP_App * pApp = XAP_App::getApp();
	UT_return_val_if_fail(pApp,FALSE);
	if(pApp->isBonoboRunning())
		return FALSE;

	UT_ASSERT(pApp->getMenuActionSet());

	const EV_EditMethodContainer * pEMC = pApp->getEditMethodContainer();
	UT_return_val_if_fail(pEMC,FALSE);


	const EV_EditMethod * pEM = pEMC->findEditMethodByName("closeWindowX");
	UT_ASSERT_HARMLESS(pEM);

	if (pEM)
	{
		if (pEM->Fn(pFrame->getCurrentView(),NULL))
		{


			return FALSE;
		}
	}


	return TRUE;
}
