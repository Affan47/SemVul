XmtLayoutConvertSizeToPixels(Widget w, double size,XmtLayoutUnitType units)
#else
int XmtLayoutConvertSizeToPixels(w, size, units)
Widget w;
double size;
XmtLayoutUnitType units;
#endif
{
    XmtLayoutWidget lw = (XmtLayoutWidget) w;

    XmtAssertWidgetClass(w, xmtLayoutWidgetClass,
			 "XmtLayoutConvertSizeToPixels");


    switch(units) {
    case XmtLayoutPoints:
	size /= 72;
    case XmtLayoutInches:
	size *= 25.4;
    case XmtLayoutMillimeters:
	size *= lw->layout.pixpermm;
	break;
    case XmtLayoutEns:
	size /= 2;
    case XmtLayoutEms:
	size *= lw->layout.pixperem;
	break;
    }


    return (int) size;
}
