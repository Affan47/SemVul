MovePageStart() {
    if (Row <= TopRow)
        return 0;
    Row = TopRow;
    NeedsUpdate = 1;
    return 1;
}
