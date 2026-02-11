getBubbleBlocker()
{
	if(isAnnotationPreviewActive())
		killAnnotationPreview();

	UT_DEBUGMSG(("FV_View::getBubbleBlocker()\n"));

	FV_View_BubbleBlocker ret( this );
	return ret;
}
