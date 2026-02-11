s_loadImage (const UT_ByteBuf & bytes, FV_View * pView, XAP_Frame * pF, gint x, gint y)
{
	FG_Graphic    * pFG  = 0;
	UT_Error error = IE_ImpGraphic::loadGraphic(bytes, 0, &pFG);
	if (error != UT_OK || !pFG)
		{
			UT_DEBUGMSG(("JK: could not import graphic from data buffer\n"));
			return;
		}
	UT_sint32 xoff = static_cast<AP_UnixFrame*>(pF)->getDocumentAreaXoff();
	UT_sint32 yoff = static_cast<AP_UnixFrame*>(pF)->getDocumentAreaYoff();
	UT_sint32 mouseX = x - xoff;
	UT_sint32 mouseY = y - yoff;
	UT_DEBUGMSG(("x %d newX %d y %d newY %d ",y,xoff,y,yoff));
	if(pView && pView->getGraphics())
		mouseX = pView->getGraphics()->tlu(mouseX);
	if(pView && pView->getGraphics())
		mouseY = pView->getGraphics()->tlu(mouseY);

	pView->cmdInsertPositionedGraphic(pFG,mouseX,mouseY);
	DELETEP(pFG);
}
