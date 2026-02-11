ChangeManaged(w)
Widget w;
{
    XbaeCaptionWidget cw = (XbaeCaptionWidget)w;
    Dimension width, height;
    XtGeometryResult result;


    if (!HaveUserChild(cw)) {
        width = LabelChild(cw)->core.width;
        height = LabelChild(cw)->core.height;
    }
    else {
        ComputeSize(cw, &width, &height,
                    UserChild(cw)->core.width, UserChild(cw)->core.height,
                    UserChild(cw)->core.border_width);
    }


    if (width != cw->core.width || height != cw->core.height) {
        do {
            result = XtMakeResizeRequest((Widget)cw, width, height,
                                         &width, &height);
        } while (result == XtGeometryAlmost);
    }


    Layout(cw, True);
}
