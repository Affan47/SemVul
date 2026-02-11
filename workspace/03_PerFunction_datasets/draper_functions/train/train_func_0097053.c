Clear(void)
{
    int i;
    for(i = A1; i <= H8; ++i)
    {
        Board[i] = EMPTY;
    }
    for(i = WK; i <= BP; ++i)
    {
        Material[i] = 0;
        for(unsigned int j = 0; j < 8; ++j)
        {
            NumOnRank[i][j] = NumOnFyle[i][j] = 0;
        }
        for(unsigned int d = 0; d < 15; ++d)
        {
            NumOnLeftDiag[i][d] = NumOnRightDiag[i][d] = 0;
        }
        NumOnSquareColor[i][WHITE] = NumOnSquareColor[i][BLACK] = 0;
    }
    Count[WHITE] = Count[BLACK] = 0;
    EPTarget = NULL_SQUARE;
    Castling = 0;
    Board [NULL_SQUARE] = END_OF_BOARD;
    PlyCounter = 0;
    HalfMoveClock = 0;
    Hash = 0;
    PawnHash = 0;
    return;
}
