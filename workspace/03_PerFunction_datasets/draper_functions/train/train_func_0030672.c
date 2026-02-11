RegisterImage(StringConst name, ImageType type, XtPointer data)
#else
static void RegisterImage(name, type, data)
StringConst name;
ImageType type;
XtPointer data;
#endif
{
    XrmQuark q = XrmStringToQuark(name);
    ImageCacheEntry *ie;

    if (image_cache == NULL) {
	image_cache = XmtHashTableCreate(3);
	pixmap_to_image_table = XmtHashTableCreate(3);
    }


    if (XmtHashTableLookup(image_cache, (XtPointer)q, (XtPointer *)&ie)) {
	if (ie->list == NULL) FreeImageCacheEntry(ie);
	else ie->orphan = True;
    }

    ie = XtNew(ImageCacheEntry);
    ie->type = type;
    if (type == ImageTypeXbm) ie->data.xbm = (XbmImage *) data;
    else ie->data.xpm = (XmtImage *)data;
    ie->orphan = False;
    ie->list = NULL;
    XmtHashTableStore(image_cache, (XtPointer)q, (XtPointer)ie);
}
