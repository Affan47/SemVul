ConPutLine(int X, int Y, int W, int H, PCell Cell) {
    for (int i = 0; i < H; ++i)
        if (ConPutBox(X, Y + i, W, 1, Cell) != 0)
            return 0;

    return 1;
}
