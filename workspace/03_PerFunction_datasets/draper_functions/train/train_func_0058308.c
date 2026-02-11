setSize(int width, int height) {
    if (width != fWidth || height != fHeight) {
        fWidth = width;
        fHeight = height;

        if (flags & wfCreated)
            if (!nullGeometry())
                XResizeWindow(xapp->display(), fHandle, fWidth, fHeight);

        configure(YRect(x(), y(), fWidth, fHeight));
    }
}
