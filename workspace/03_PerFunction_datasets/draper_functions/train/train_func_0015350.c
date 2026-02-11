unstackEnemy (const int spriteId,
                                   const int gridI, const int gridJ,
                                   const int prevEnemy)
{
    dbe2 "KGrLevelPlayer::unstackEnemy (%02d at [%02d,%02d] prevEnemy %02d)\n",
        spriteId, gridI, gridJ, prevEnemy);
    int nextId = grid->enemyOccupied (gridI, gridJ);
    int prevId;
    while (nextId > 0) {
        prevId = enemies.at (nextId - 1)->getPrevInCell();
        dbe2 "Next %02d prev %02d\n", nextId, prevId);
        if (prevId == spriteId) {
            dbe2 "    SET IDs - id %02d prev %02d\n", nextId, prevEnemy);
            enemies.at (nextId - 1)->setPrevInCell (prevEnemy);

        }
        nextId = prevId;
    }
}
