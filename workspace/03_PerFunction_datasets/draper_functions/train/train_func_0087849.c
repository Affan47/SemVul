TabularColumnPosition(TabularT *table, int n)


{
    int i, oldWidth;
    int colWidth;

    colWidth = 0;
    for (i=1; i<=n; i++)
        colWidth += table->width[i];

    oldWidth = getLength("textwidth") * (n ) / (table->n );

    diagnostics(5,"col=%3d old=%5d new=%5d",n,oldWidth,colWidth);
    return (int) colWidth;
}
