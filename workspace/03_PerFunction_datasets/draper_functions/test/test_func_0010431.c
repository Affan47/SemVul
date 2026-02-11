getPiece()
{
    pieceIndex++;

    if (pieceIndex > maxCapacity)
    {
        pieceIndex = 0;
        genList(maPieceList[0]);
    }

    return maPieceList[pieceIndex];
}
