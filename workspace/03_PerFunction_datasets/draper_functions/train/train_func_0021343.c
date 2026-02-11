CanBeUnload() const
{

    return MapPersistentState::CanBeUnload() && !HasBounds() && !HasRespawnTimes();
}
