GetValuesHook(w, args, num_args)
Widget w;
ArgList args;
Cardinal *num_args;
{
    XbaeCaptionWidget cw = (XbaeCaptionWidget)w;
    int i;


    for (i = 0; i < *num_args; i++)
        if (strcmp(args[i].name, XmNlabelString) == 0)
            XtGetValues(LabelChild(cw), &args[i], 1);
        else if (strcmp(args[i].name, XmNfontList) == 0)
            XtGetValues(LabelChild(cw), &args[i], 1);
}
