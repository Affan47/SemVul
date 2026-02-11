ImgPictDisplay(clientData, display, drawable, imageX, imageY, width,
	height, drawableX, drawableY)
    ClientData clientData;

    Display *display;
    Drawable drawable;
    int imageX, imageY;

    int width, height;
    int drawableX, drawableY;

{
    PictInstance *instancePtr = (PictInstance *) clientData;

#ifdef DEBUG
    printf("ImgPictDisplay\n");
#endif


    if (instancePtr->pixels == None) {
	return;
    }


    XSetRegion(display, instancePtr->gc, instancePtr->masterPtr->validRegion);
    XSetClipOrigin(display, instancePtr->gc, drawableX - imageX,
	    drawableY - imageY);
    XCopyArea(display, instancePtr->pixels, drawable, instancePtr->gc,
	    imageX, imageY, (unsigned) width, (unsigned) height,
	    drawableX, drawableY);
    XSetClipMask(display, instancePtr->gc, None);
    XSetClipOrigin(display, instancePtr->gc, 0, 0);
}
