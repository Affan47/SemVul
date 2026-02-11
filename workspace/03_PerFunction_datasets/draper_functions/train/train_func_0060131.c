TryAllMoves(ChipColor opponent, int level, int cutoffval,
                        quint64 opponentbits, quint64 colorbits)
{
    int maxval = -LARGEINT;


    yield();

    quint64  null_bits;
    null_bits = 0;

    for (int x = 1; x < 9; x++) {
        for (int y = 1; y < 9; y++) {
            if (m_board[x][y] == NoColor
                    && (m_neighbor_bits[x][y] & colorbits) != null_bits) {
                int val = ComputeMove2(x, y, opponent, level + 1, maxval, opponentbits,
                                       colorbits);

                if (val != ILLEGAL_VALUE && val > maxval) {
                    maxval = val;
                    if (maxval > -cutoffval || interrupted())
                        break;
                }
            }
        }

        if (maxval > -cutoffval || interrupted())
            break;
    }

    if (interrupted())
        return -LARGEINT;

    return maxval;
}
