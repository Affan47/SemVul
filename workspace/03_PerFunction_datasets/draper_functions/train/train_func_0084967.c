PrintFEN(char * str, unsigned int flags)
{
    ASSERT(str != NULL);
    unsigned int emptyRun, iRank, iFyle;
    pieceT * pBoard = Board;
    for(iRank = 0; iRank < 8; ++iRank)
    {
        pBoard = &(Board[(7 - iRank) * 8]);
        emptyRun = 0;
        if(iRank > 0  &&  flags > FEN_COMPACT)
        {
            *str++ = '/';
        }
        for(iFyle = 0; iFyle < 8; ++iFyle, ++pBoard)
        {
            if(*pBoard != EMPTY)
            {
                if(emptyRun)
                {
                    *str++ = (unsigned char) emptyRun + '0';
                }
                emptyRun = 0;
                *str++ = PIECE_CHAR[*pBoard];
            }
            else
            {
                ++emptyRun;
            }
        }
        if(emptyRun)
        {
            *str++ = (unsigned char) emptyRun + '0';
        }
    }

    if(flags > FEN_COMPACT)
    {
        *str++ = ' ';
    }
    *str++ = (ToMove == WHITE ? 'w' : 'b');
    *str = 0;

    if(flags >= FEN_CASTLING_EP)
    {

        *str++ = ' ';
        if(Castling == 0)
        {
            *str++ = '-';
        }
        else
        {
            if(GetCastling(WHITE, KSIDE))
            {
                *str++ = 'K';
            }
            if(GetCastling(WHITE, QSIDE))
            {
                *str++ = 'Q';
            }
            if(GetCastling(BLACK, KSIDE))
            {
                *str++ = 'k';
            }
            if(GetCastling(BLACK, QSIDE))
            {
                *str++ = 'q';
            }
        }
        *str++ = ' ';


        if(EPTarget == NULL_SQUARE)
        {
            *str++ = '-';
        }
        else
        {
            *str++ = square_FyleChar(EPTarget);
            *str++ = square_RankChar(EPTarget);
        }
        *str = 0;

        if(flags >= FEN_ALL_FIELDS)
        {

            *str++ = ' ';
            sprintf(str, "%d %d", HalfMoveClock, (PlyCounter / 2) + 1);
        }
    }
    return;
}
