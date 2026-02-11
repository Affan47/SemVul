HandleResetStatsCommand(char* args)
{
    Player* target;
    if (!ExtractPlayerTarget(&args, &target))
        return false;

    if (!HandleResetStatsOrLevelHelper(target))
        return false;

    target->InitRunes();
    target->InitStatsForLevel(true);
    target->InitTaxiNodesForLevel();
    target->InitGlyphsForLevel();
    target->InitTalentForLevel();

    return true;
}
