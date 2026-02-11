drawHiddenShips(Sea::Player winner)
{
    QList<Ship *> enemyShips = m_sea->enemyShips();

    foreach (Ship * ship, enemyShips) {
        if (ship->alive()) {
            m_seaview->add(winner, ship);
        }
    }
}
