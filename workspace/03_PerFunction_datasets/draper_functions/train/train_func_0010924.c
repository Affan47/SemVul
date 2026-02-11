heuristic(const Map &map)
{
    if (map.my_pos() == map.enemy_pos())
        return 0;

    int playerMoves = map.cntMoves(SELF);
    int enemyMoves = map.cntMoves(ENEMY);

    if (!playerMoves && enemyMoves)
        return -INF;
    if (playerMoves && !enemyMoves)
        return INF;
    if (!playerMoves && !enemyMoves)
        return 0;


    {
        const TranspositionTable::Entry *entry = trans_table.get(map.hash());
        if (entry)
            return entry->heuristic;
    }

    int ret;
    if (isOpponentIsolated(map)) {
        int cntPlayer = countReachableSquares(map, SELF);
        int cntEnemy = countReachableSquares(map, ENEMY);
        ret = cntPlayer - cntEnemy;
    } else {
        int voronoi = voronoiTerritory(map);
        ret = voronoi;
    }

    TranspositionTable::Entry entry;
    entry.heuristic = ret;

    trans_table.set(map.hash(), entry);
    return ret;
}
