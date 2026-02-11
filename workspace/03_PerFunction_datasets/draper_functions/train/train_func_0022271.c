xbaeCopyColumnLabelAlignments(mw)
XbaeMatrixWidget mw;
{
    unsigned char *copy = NULL;
    int i;
    Boolean bad = False;

    if (mw->matrix.columns)
    {
        copy = (unsigned char *) XtMalloc(mw->matrix.columns *
                                          sizeof(unsigned char));

        for (i = 0; i < mw->matrix.columns; i++)
        {
            if (!bad &&
                mw->matrix.column_label_alignments[i] == BAD_ALIGNMENT)
            {
                bad = True;
                XtAppWarningMsg(
                    XtWidgetToApplicationContext((Widget) mw),
                    "copyColumnLabelAlignments", "tooShort",
                    "XbaeMatrix",
                    "XbaeMatrix: Column label alignments array is too short",
                    NULL, 0);
                copy[i] = XmALIGNMENT_BEGINNING;
            }
            else if (bad)
                copy[i] = XmALIGNMENT_BEGINNING;
            else
                copy[i] = mw->matrix.column_label_alignments[i];
        }
    }
    mw->matrix.column_label_alignments = copy;
}
