calculateAccess (bool pRunThruHole)
{
    runThruHole = pRunThruHole;

    char here;
    bool canEnter;


    for (int j = 1; j < height - 1; j++) {
        for (int i = 1; i < width - 1; i++) {
            here      = cellType (i, j);
            canEnter  = (here != BRICK)  && (here != CONCRETE) &&
                        (here != FBRICK) && (here != USEDHOLE);
            heroAccess  [index (i, j)] = canEnter ? ENTERABLE : 0;
            enemyAccess [index (i, j)] = canEnter ? ENTERABLE : 0;
        }
    }


    for (int j = 1; j < height - 1; j++) {
        for (int i = 1; i < width - 1; i++) {
            calculateCellAccess (i, j);
        }
    }
}
