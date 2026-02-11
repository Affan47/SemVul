runModal(XAP_Frame * pFrame)
{
	UT_ASSERT(pFrame);

	GtkWidget * cf = constructWindow();
	UT_return_if_fail(cf);

	abiRunModalDialog ( GTK_DIALOG(cf), pFrame, this, GTK_RESPONSE_CLOSE,false );
	abiDestroyWidget(cf);
}
