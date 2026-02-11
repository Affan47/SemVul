get(
    Display& d, Pixmap pix, int width, int height, const Raster* ras
) {
    XImage* ret = nil;

    if (ras && (pix == ras->rep()->pixmap_)) {
        ret = ras->rep()->image_;
    }
    else {
        ImageHolder* ih = nil;
        if (!_table.find(ih, pix)) {
            XDisplay* dpy = d.rep()->display_;
            ih = new ImageHolder;

#ifdef XSHM
            RasterRep::init_shared_memory(
                ih->_shared_memory, d, ih->_shminfo, width, height, ih->_image,
                pix
            );
#endif

            if (!ih->_shared_memory) {
                ih->_image = XGetImage(
                    dpy, pix, 0, 0, width, height, AllPlanes, ZPixmap
                );
            }

            _table.insert(pix, ih);
        }
        ret = ih->_image;
    }

    return ret;
}
