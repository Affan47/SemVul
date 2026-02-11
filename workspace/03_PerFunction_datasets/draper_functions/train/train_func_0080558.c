xbaeCopyColumnWidths(mw)
XbaeMatrixWidget mw;
{
    short *copy = NULL;
    int i;
    Boolean bad = False;

    if (mw->matrix.columns)
    {
        copy = (short *) XtMalloc(mw->matrix.columns * sizeof(short));

        for (i = 0; i < mw->matrix.columns; i++)
        {
            if (!bad && mw->matrix.column_widths[i] == BAD_WIDTH)
            {
                bad = True;
                XtAppWarningMsg(
                    XtWidgetToApplicationContext((Widget) mw),
                    "copyColumnWidths", "tooShort", "XbaeMatrix",
                    "XbaeMatrix: Column widths array is too short",
                    NULL, 0);
                copy[i] = 1;
            }
            else if (bad)
                copy[i] = 1;
            else
                copy[i] = mw->matrix.column_widths[i];
        }
    }
    mw->matrix.column_widths = copy;
}
