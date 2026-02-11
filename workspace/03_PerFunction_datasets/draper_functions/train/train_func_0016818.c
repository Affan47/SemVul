ResizeCells(current, new)
XbaeMatrixWidget current;
XbaeMatrixWidget new;
{
    int i, j;
    int safe_rows = 0;


    if (!new->matrix.cells)
        return;

    if (new->matrix.rows == current->matrix.rows)
        safe_rows = new->matrix.rows;


    if (new->matrix.rows > current->matrix.rows)
    {


        new->matrix.cells =
            (String **) XtRealloc((char *) new->matrix.cells,
                                  new->matrix.rows * sizeof(String *));


        for (i = current->matrix.rows; i < new->matrix.rows; i++)
        {
            new->matrix.cells[i] =
                (String *) XtMalloc(new->matrix.columns * sizeof(String));
            for (j = 0; j < new->matrix.columns; j++)
                new->matrix.cells[i][j] = XtNewString("");
        }

        safe_rows = current->matrix.rows;
    }


    if (new->matrix.rows < current->matrix.rows)
    {


        for (i = new->matrix.rows; i < current->matrix.rows; i++)
        {
            for (j = 0; j < current->matrix.columns; j++)
                XtFree((XtPointer) new->matrix.cells[i][j]);
            XtFree((XtPointer) new->matrix.cells[i]);
        }

        safe_rows = new->matrix.rows;
    }


    if (new->matrix.columns > current->matrix.columns)
    {


        for (i = 0; i < safe_rows; i++)
        {
            new->matrix.cells[i] =
                (String *) XtRealloc((char *) new->matrix.cells[i],
                                     new->matrix.columns * sizeof(String));
            for (j = current->matrix.columns; j < new->matrix.columns; j++)
                new->matrix.cells[i][j] = XtNewString("");
        }
    }


    if (new->matrix.columns < current->matrix.columns)
    {


        for (i = 0; i < safe_rows; i++)
            for (j = new->matrix.columns; j < current->matrix.columns; j++)
                XtFree((XtPointer) new->matrix.cells[i][j]);
    }
}
