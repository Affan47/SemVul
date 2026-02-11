NET_ValidGameSettings(GameMode_t mode, GameMission_t mission,
                              net_gamesettings_t *settings)
{
    if (settings->ticdup <= 0)
        return false;

    if (settings->extratics < 0)
        return false;

    if (settings->deathmatch < 0 || settings->deathmatch > 2)
        return false;

    if (settings->skill < sk_noitems || settings->skill > sk_nightmare)
        return false;

    if (!D_ValidGameVersion(mission, settings->gameversion))
        return false;

    if (!D_ValidEpisodeMap(mission, mode, settings->episode, settings->map))
        return false;

    return true;
}
