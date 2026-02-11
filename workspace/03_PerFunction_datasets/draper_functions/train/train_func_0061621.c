defaultStrategy(Sea::Player player, Sea* sea)
{
    if (m_random) {
        return new RandomStrategy(player, sea, *this);
    }
    else {
        for (int i = m_config->longestShip() - 1; i >= 0; i--) {
            if (m_ships[i] > 0 || i == 0) {
                return new DiagonalStrategy(player, sea, *this, i + 1);
            }
        }


        return 0;
    }
}
