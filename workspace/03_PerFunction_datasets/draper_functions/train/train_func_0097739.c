Initialize(req, new, args, num_args)
Widget req;
Widget new;
ArgList args;
Cardinal *num_args;
{
    ICLabelWidget iclw = (ICLabelWidget)new;

    if (iclw->iclabel.label != NULL) {
	iclw->iclabel.label = copyString(iclw->iclabel.label);
    }
    iclw->iclabel.width = 0;
}
