emptyRow(int rowNum) {
    Row &r = *grid[rowNum].row;
    const int s = r.size();
    RenderTableCell *cell;
    for(int i=0; i<s; i++) {
        cell = r[i];
        if (!cell || cell==(RenderTableCell*)-1)
            continue;
        return false;
    }
    return true;
}
