IsKingInCheckDir(directionT dir)
{
    ASSERT(dir != NULL_DIR);
    squareT kingSq = GetKingSquare(ToMove);
    colorT enemy = color_Flip(ToMove);
    bool isDiagonal = direction_IsDiagonal(dir);
    pieceT queen = piece_Make(enemy, QUEEN);
    pieceT slider = piece_Make(enemy, (isDiagonal ? BISHOP : ROOK));


    unsigned int nSliders = PieceCount(queen) + PieceCount(slider);
    if(nSliders == 0)
    {
        return false;
    }


    fyleT fyle = square_Fyle(kingSq);
    rankT rank = square_Rank(kingSq);
    leftDiagT ldiag = square_LeftDiag(kingSq);
    rightDiagT rdiag = square_RightDiag(kingSq);

    switch(dir)
    {
    case UP:
    case DOWN:
        nSliders = FyleCount(queen, fyle) + FyleCount(slider, fyle);
        break;
    case LEFT:
    case RIGHT:
        nSliders = RankCount(queen, rank) + RankCount(slider, rank);
        break;
    case UP_LEFT:
    case DOWN_RIGHT:
        nSliders = LeftDiagCount(queen, ldiag) + LeftDiagCount(slider, ldiag);
        break;
    case UP_RIGHT:
    case DOWN_LEFT:
        nSliders = RightDiagCount(queen, rdiag) + RightDiagCount(slider, rdiag);
        break;
    }
    if(nSliders == 0)
    {
        return false;
    }


    squareT dest = kingSq;
    squareT last = square_Last(kingSq, dir);
    int delta = direction_Delta(dir);

    while(dest != last)
    {
        dest += delta;
        pieceT p = Board[dest];
        if(p == EMPTY)
        {

        }
        else if(p == queen  ||  p == slider)
        {

            return true;
        }
        else
        {

            break;
        }
    }

    return false;
}
