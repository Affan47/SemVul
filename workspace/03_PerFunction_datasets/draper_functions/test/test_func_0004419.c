MoveFlyOrLand(uint32 id, float x, float y, float z, bool liftOff)
{
    if (m_owner->GetTypeId() != TYPEID_UNIT)
        return;

    DEBUG_FILTER_LOG(LOG_FILTER_AI_AND_MOVEGENSS, "%s targeted point for %s (Id: %u X: %f Y: %f Z: %f)", m_owner->GetGuidStr().c_str(), liftOff ? "liftoff" : "landing", id, x, y, z);
    Mutate(new FlyOrLandMovementGenerator(id, x, y, z, liftOff));
}
