hashEpSquare()
{
    int epSquareIndex;
    Square sq = enPassantSquare();
    if(sq >= 16 && sq <= 23)
    {
        epSquareIndex = sq - 16;
    }
    else if(sq >= 40 && sq <= 47)
    {
        epSquareIndex = sq - 32;
    }
    else
    {
        return;
    }
    m_hashValue ^= RAND_EN_PASSANT[epSquareIndex];
}
