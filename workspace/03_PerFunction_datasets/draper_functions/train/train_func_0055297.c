changeCellAt (const int i, const int j, const char type)
{
    int  position          = index (i, j);
    bool canEnter          = (type != BRICK) && (type != CONCRETE) &&
                             (type != FBRICK) && (type != USEDHOLE);
    layout      [position] = type;
    heroAccess  [position] = canEnter ? ENTERABLE : 0;
    enemyAccess [position] = canEnter ? ENTERABLE : 0;

    calculateCellAccess (i, j);

    calculateCellAccess (i, j - 1);
    calculateCellAccess (i - 1, j);
    calculateCellAccess (i + 1, j);
    calculateCellAccess (i, j + 1);
}
