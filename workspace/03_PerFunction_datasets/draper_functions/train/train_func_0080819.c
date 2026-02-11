UnBoard(Unit* passenger, bool changeVehicle)
{
    MANGOS_ASSERT(passenger);

    DEBUG_LOG("VehicleInfo::Unboard: passenger: %s", passenger->GetGuidStr().c_str());

    PassengerMap::const_iterator itr = m_passengers.find(passenger);
    MANGOS_ASSERT(itr != m_passengers.end());

    VehicleSeatEntry const* seatEntry = GetSeatEntry(itr->second->GetTransportSeat());
    MANGOS_ASSERT(seatEntry);

    UnBoardPassenger(passenger);

    if (!changeVehicle)
    {

        passenger->m_movementInfo.RemoveMovementFlag(MOVEFLAG_ONTRANSPORT);
        passenger->m_movementInfo.ClearTransportData();

        if (passenger->GetTypeId() == TYPEID_PLAYER)
        {
            Player* pPlayer = (Player*)passenger;
            pPlayer->ResummonPetTemporaryUnSummonedIfAny();


        }

        if (passenger->IsRooted())
            passenger->SetRoot(false);

        Movement::MoveSplineInit init(*passenger);

        init.MoveTo(m_owner->GetPositionX(), m_owner->GetPositionY(), m_owner->GetPositionZ());
        init.SetExitVehicle();
        init.Launch();


        if (passenger->GetTypeId() == TYPEID_UNIT && m_accessoryGuids.find(passenger->GetObjectGuid()) != m_accessoryGuids.end())
        {
            Creature* cPassenger = static_cast<Creature*>(passenger);

            cPassenger->ForcedDespawn(5000);
            m_accessoryGuids.erase(passenger->GetObjectGuid());
        }
    }


    RemoveSeatMods(passenger, seatEntry->m_flags);


    if (m_owner->GetTypeId() == TYPEID_UNIT)
    {


        if ((seatEntry->m_flags & SEAT_FLAG_CAN_CONTROL) &&
                !(m_vehicleEntry->m_flags & (VEHICLE_FLAG_UNK4 | VEHICLE_FLAG_UNK20)))
        {
            if (((Creature*)m_owner)->IsTemporarySummon())
                ((Creature*)m_owner)->ForcedDespawn(1000);
        }
    }
}
