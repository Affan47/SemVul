GetLevelForTarget(Unit const* target) const
{
    if (!IsWorldBoss())
        return Unit::GetLevelForTarget(target);

    uint32 level = target->getLevel() + sWorld.getConfig(CONFIG_UINT32_WORLD_BOSS_LEVEL_DIFF);
    if (level < 1)
        return 1;
    if (level > 255)
        return 255;
    return level;
}
