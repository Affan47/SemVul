Tk_PictExpand(handle, width, height)
    Tk_PictHandle handle;
    int width, height;
{
    PictMaster *masterPtr;

#ifdef DEBUG
    printf("Tk_PictExpand\n");
#endif

    masterPtr = (PictMaster *) handle;

    if (width <= masterPtr->width) {
	width = masterPtr->width;
    }
    if (height <= masterPtr->height) {
	height = masterPtr->height;
    }

    if ((width != masterPtr->width) || (height != masterPtr->height)) {
	ImgPictSetSize(masterPtr, MAX(width, masterPtr->width),
		MAX(height, masterPtr->height));
	Tk_ImageChanged(masterPtr->tkMaster, 0, 0, 0, 0, masterPtr->width,
		masterPtr->height);
    }
}
