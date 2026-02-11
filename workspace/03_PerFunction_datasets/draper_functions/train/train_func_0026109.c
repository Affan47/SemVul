showEnemyState (int enemyId)
{
    if (enemyId < enemies.count()) {
        enemies.at(enemyId)->showState();
    }
}
