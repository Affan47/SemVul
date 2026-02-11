KBBK(Position * pos)
{
    unsigned char * material = pos->GetMaterial();
    squareT wk, bk, wb1, wb2;
    colorT stm = pos->GetToMove();


    if(material[WB] == 2)
    {
        wk = pos->GetKingSquare(WHITE);
        bk = pos->GetKingSquare(BLACK);
        squareT * sqlist = pos->GetList(WHITE);
        wb1 = sqlist[1];
        wb2 = sqlist[2];
    }
    else
    {
        ASSERT(material[BB] == 2);
        wk = square_FlipRank(pos->GetKingSquare(BLACK));
        bk = square_FlipRank(pos->GetKingSquare(WHITE));
        squareT * sqlist = pos->GetList(BLACK);
        wb1 = square_FlipRank(sqlist[1]);
        wb2 = square_FlipRank(sqlist[2]);
        stm = color_Flip(stm);
    }


    if(square_Color(wb1) == square_Color(wb2))
    {
        return DRAW;
    }


    if(stm == BLACK)
    {
        if(square_Adjacent(bk, wb1))
        {
            return UNKNOWN;
        }
        if(square_Adjacent(bk, wb2))
        {
            return UNKNOWN;
        }
        if(square_IsEdgeSquare(bk)  &&  square_Distance(wk, bk) == 2)
        {
            return UNKNOWN;
        }
    }


    int bkCorner = square_Distance(bk, square_NearestCorner(bk));
    int kingDist = square_Distance(bk, wk);


    int score = 900 + (25 * bkCorner) - (10 * kingDist);
    int winValue = recogValue(SCORE_LOWER, score);
    int lossValue = recogValue(SCORE_UPPER, -score);
    return (stm == WHITE) ? winValue : lossValue;
}
