Initialize()
{
    if (!m_overwriteNpcEntry)
        m_overwriteNpcEntry = m_owner->GetEntry();


    SQLMultiStorage::SQLMSIteratorBounds<VehicleAccessory> bounds = sVehicleAccessoryStorage.getBounds<VehicleAccessory>(m_overwriteNpcEntry);
    for (SQLMultiStorage::SQLMultiSIterator<VehicleAccessory> itr = bounds.first; itr != bounds.second; ++itr)
    {
        if (Creature* summoned = m_owner->SummonCreature(itr->passengerEntry, m_owner->GetPositionX(), m_owner->GetPositionY(), m_owner->GetPositionZ(), 2 * m_owner->GetOrientation(), TEMPSUMMON_DEAD_DESPAWN, 0))
        {
            DEBUG_LOG("VehicleInfo(of %s)::Initialize: Load vehicle accessory %s onto seat %u", m_owner->GetGuidStr().c_str(), summoned->GetGuidStr().c_str(), itr->seatId);
            m_accessoryGuids.insert(summoned->GetObjectGuid());
            int32 basepoint0 = itr->seatId + 1;
            summoned->CastCustomSpell((Unit*)m_owner, SPELL_RIDE_VEHICLE_HARDCODED, &basepoint0, NULL, NULL, true);
        }
    }
    m_isInitialized = true;
}
