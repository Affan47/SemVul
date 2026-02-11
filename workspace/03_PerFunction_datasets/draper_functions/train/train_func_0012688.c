ReadFromLongStr(const char * str)
{
    pieceT pieceFromByte [256] = {EMPTY};
    pieceFromByte [(int) 'K'] = WK;
    pieceFromByte [(int) 'k'] = BK;
    pieceFromByte [(int) 'Q'] = WQ;
    pieceFromByte [(int) 'q'] = BQ;
    pieceFromByte [(int) 'R'] = WR;
    pieceFromByte [(int) 'r'] = BR;
    pieceFromByte [(int) 'B'] = WB;
    pieceFromByte [(int) 'b'] = BB;
    pieceFromByte [(int) 'N'] = WN;
    pieceFromByte [(int) 'n'] = BN;
    pieceFromByte [(int) 'P'] = WP;
    pieceFromByte [(int) 'p'] = BP;

    Clear();
    for(squareT sq = A1; sq <= H8; ++sq)
    {
        if(str[sq] == '.')
        {
            continue;
        }
        pieceT p = pieceFromByte [(unsigned char) str[sq]];
        if(p == EMPTY)
        {
            return ERROR_Corrupt;
        }
        if(AddPiece(p, sq) != OK)
        {
            return ERROR_Corrupt;
        }
    }
    switch(str[65])
    {
    case 'w':
        SetToMove(WHITE);
        break;
    case 'b':
        SetToMove(BLACK);
        break;
    default:
        return ERROR_Corrupt;
    }
    return OK;
}
