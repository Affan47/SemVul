GetLevelSetDoc() const {
    if(GetDocument() == NULL || !GetDocument()->IsKindOf(CLASSINFO(LevelSetDoc)))
        return NULL;
    return (LevelSetDoc*) GetDocument();
}
