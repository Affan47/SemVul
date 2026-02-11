ComputeFirstMove(const KReversiGame& game)
{
    int    r;
    ChipColor  color = game.currentPlayer();

    r = m_random.getLong(4) + 1;

    if (color == White) {
        if (r == 1)      return  KReversiMove(color, 4, 2);
        else if (r == 2) return  KReversiMove(color, 5, 3);
        else if (r == 3) return  KReversiMove(color, 2, 4);
        else             return  KReversiMove(color, 3, 5);
    } else {
        if (r == 1)      return  KReversiMove(color, 3, 2);
        else if (r == 2) return  KReversiMove(color, 5, 4);
        else if (r == 3) return  KReversiMove(color, 2, 3);
        else             return  KReversiMove(color, 4, 5);
    }
}
