Add() {
    if(levels.empty())
        return true;
    if(document == NULL)
        return false;
    LevelSet* levelset = document->GetLevelSet();
    if(levelset == NULL)
        return false;
    if(index > levelset->GetLevelCount())
        index = levelset->GetLevelCount();
    wxUint16 n = index;
    std::vector<CountedPtr<Level> >::const_iterator it;
    for(it = levels.begin(); it != levels.end(); ++it) {
        if(!levelset->InsertLevel(*it, n))
            break;
        ++n;
    }
    if(it != levels.end()) {
        while(n > index) {
            --n;
            levelset->RemoveLevel(n);
        }
        return false;
    }
    document->Modify(true);
    LevelUpdateHint hint;
    hint.type = LevelUpdateHint::CREATE;
    if(levels.size() == 1)
        hint.level = levels.front();
    document->UpdateAllViews(NULL, &hint);
    return true;
}
