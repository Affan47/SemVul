CalculateRewardHonor(uint32 level) const
{
    if (level > GT_MAX_LEVEL)
        level = GT_MAX_LEVEL;

    uint32 honor = 0;

    if (GetRewHonorAddition() > 0 || GetRewHonorMultiplier() > 0.0f)
    {

        TeamContributionPoints const* tc = sTeamContributionPoints.LookupEntry(level - 1);
        if (!tc)
            return 0;
        uint32 i_honor = uint32(tc->Value * GetRewHonorMultiplier() * 0.1f);
        honor = i_honor + GetRewHonorAddition();
    }

    return honor;
}
