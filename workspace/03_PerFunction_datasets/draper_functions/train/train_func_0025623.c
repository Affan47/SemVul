sudokuTestState(l_int32  *state,
                l_int32   index)
{
l_int32  i, j, val, row, rowstart, rowend, col;
l_int32  blockrow, blockcol, blockstart, rowindex, locindex;

    if ((val = state[index]) == 0)
        return 1;


    row = index / 9;
    rowstart = 9 * row;
    for (i = rowstart; i < index; i++) {
        if (state[i] == val)
            return 0;
    }
    rowend = rowstart + 9;
    for (i = index + 1; i < rowend; i++) {
        if (state[i] == val)
            return 0;
    }


    col = index % 9;
    for (j = col; j < index; j += 9) {
        if (state[j] == val)
            return 0;
    }
    for (j = index + 9; j < 81; j += 9) {
        if (state[j] == val)
            return 0;
    }


    blockrow = 3 * (row / 3);
    blockcol = 3 * (col / 3);
    blockstart = 9 * blockrow + blockcol;
    for (i = 0; i < 3; i++) {
        rowindex = blockstart + 9 * i;
        for (j = 0; j < 3; j++) {
            locindex = rowindex + j;
            if (index == locindex) continue;
            if (state[locindex] == val)
                return 0;
        }
    }

    return 1;
}
