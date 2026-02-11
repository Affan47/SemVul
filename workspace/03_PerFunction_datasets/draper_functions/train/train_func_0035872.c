cpento_add_move(byte *move, int x, int y, int m)
{
    int i;
    for (i=0; move[i] != -1; i += 3)
    {
        if (move[i] == x && move[i+1] == y) {
            move[i+2] = m;
            return;
        }
    }
    move[i] = x;
    move[i+1] = y;
    move[i+2] = m;
    move[i+3] = -1;
    return;
}
