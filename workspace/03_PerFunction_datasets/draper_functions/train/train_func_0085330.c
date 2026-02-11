ChangeFont(obj, fonts, mapping)
WcharDisplayObject obj;
XFontStruct **fonts;
Boolean *mapping;
{
    Boolean newgc = False;
    int i;

    for (i = 0; i < 4; i++) {
	if (fonts[i] != obj->wcharDisplay.fonts[i] ||
	    mapping[i] != obj->wcharDisplay.grmapping[i]) {
	    obj->wcharDisplay.fonts[i] = fonts[i];
	    obj->wcharDisplay.grmapping[i] = mapping[i];
	    newgc = True;
	}
    }
    if (newgc) {
	XtWSReleaseGCSet((Widget)obj, obj->wcharDisplay.gcset_normal);
	XtWSReleaseGCSet((Widget)obj, obj->wcharDisplay.gcset_rev);
	GetGC(obj);
    }
}
