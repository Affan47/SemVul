observeEntity()
{
    mAttrChangedSlot.disconnect();
    if (mEntity) {
        mAttrChangedSlot = sigc::mem_fun(*this, &TerrainModObserver::attributeChanged);
        mEntity->observe("terrainmod", mAttrChangedSlot);
        mEntity->Moved.connect(sigc::mem_fun(*this, &TerrainModObserver::entity_Moved));
        mEntity->BeingDeleted.connect(sigc::mem_fun(*this, &TerrainModObserver::entity_Deleted));
    }
}
