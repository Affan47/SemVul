SetMonsters(const std::list<MonsterRecord>& monsters) {
    if(document == NULL || level == NULL)
        return false;
    level->monsters = monsters;
    document->Modify(true);
    LevelUpdateHint hint;
    hint.type = LevelUpdateHint::MONSTER;
    hint.level = level;
    document->UpdateAllViews(NULL, &hint);
    return true;
}
