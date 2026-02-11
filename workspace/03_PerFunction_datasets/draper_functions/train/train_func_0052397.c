selection_start(int x, int y)
{
    D_SELECT(("selection_start(%d, %d)\n", x, y));
    selection_start_colrow(Pixel2Col(x), Pixel2Row(y));
}
