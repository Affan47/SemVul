SetLevelMonsters(CountedPtr<Level> level, const std::list<MonsterRecord>& newmonsters) {
    if(level == NULL)
        return false;
    if(newmonsters == level->monsters)
        return true;
    return GetCommandProcessor()->Submit(new LevelMonstersCommand(level, this, level->monsters, newmonsters));
}
