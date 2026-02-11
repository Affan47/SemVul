KBPK(Position * pos)
{
    unsigned char * material = pos->GetMaterial();
    squareT wk, bk;
    fyleT wrongFile = A_FYLE;


    if(material[WB] == 1)
    {
        wk = pos->GetKingSquare(WHITE);
        bk = pos->GetKingSquare(BLACK);
        if(pos->SquareColorCount(WB, WHITE) == 1)
        {
            wrongFile = H_FYLE;
        }
        if(pos->FyleCount(WP, wrongFile) != material[WP])
        {
            return UNKNOWN;
        }
    }
    else
    {
        ASSERT(material[BB] == 1);
        wk = square_FlipRank(pos->GetKingSquare(BLACK));
        bk = square_FlipRank(pos->GetKingSquare(WHITE));
        if(pos->SquareColorCount(BB, BLACK) == 1)
        {
            wrongFile = H_FYLE;
        }
        if(pos->FyleCount(BP, wrongFile) != material[BP])
        {
            return UNKNOWN;
        }
    }


    squareT promoSq = square_Make(wrongFile, RANK_8);
    if(bk == promoSq  ||  square_Adjacent(bk, promoSq))
    {
        return DRAW;
    }

    return UNKNOWN;
}
