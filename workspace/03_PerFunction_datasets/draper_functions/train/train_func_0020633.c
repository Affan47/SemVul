whitePlayerMove(KReversiMove move)
{
    if (move.color == Black)
        return;
    makeMove(move);
}
