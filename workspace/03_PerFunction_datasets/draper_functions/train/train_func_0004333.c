ScrollDown(int Rows) {
    if (TopRow == 0)
        return 0;

    TopRow -= Rows;
    Row -= Rows;

    if (Row < 0)
        Row = 0;
    if (TopRow < 0)
        TopRow = 0;
    NeedsUpdate = 1;
    return 1;
}
