turnChips(const KReversiMove &move)
{
    m_changedChips.clear();


    setChipColor(move);
    m_changedChips.append(move);

    for (int dirNum = 0; dirNum < DIRECTIONS_COUNT; dirNum++) {
        if (hasChunk(dirNum, move)) {
            for (int r = move.row + DX[dirNum], c = move.col + DY[dirNum];
                    r >= 0 && c >= 0 && r < 8 && c < 8;
                    r += DX[dirNum], c += DY[dirNum]) {
                if (m_cells[r][c] == move.color)
                    break;
                setChipColor(KReversiMove(move.color, r, c));
                m_changedChips.append(KReversiMove(move.color, r, c));
            }
        }
    }

    m_undoStack.push(m_changedChips);
}
