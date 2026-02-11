RemoveSeatMods(Unit* passenger, uint32 seatFlags)
{
    Unit* pVehicle = (Unit*)m_owner;

    if (seatFlags & SEAT_FLAG_NOT_SELECTABLE)
        passenger->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);

    if (passenger->GetTypeId() == TYPEID_PLAYER)
    {
        Player* pPlayer = (Player*)passenger;


        if (pPlayer->GetGroup())
            pPlayer->SetGroupUpdateFlag(GROUP_UPDATE_FLAG_VEHICLE_SEAT);

        if (seatFlags & SEAT_FLAG_CAN_CONTROL)
        {
            pPlayer->SetCharm(NULL);
            pVehicle->SetCharmerGuid(ObjectGuid());

            pPlayer->SetClientControl(pVehicle, 0);
            pPlayer->SetMover(NULL);

            pVehicle->clearUnitState(UNIT_STAT_CONTROLLED);
            pVehicle->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_PLAYER_CONTROLLED);


            pPlayer->GetCamera().ResetView();
        }

        if (seatFlags & SEAT_FLAG_CAN_CAST)
            pPlayer->RemovePetActionBar();
    }
    else if (passenger->GetTypeId() == TYPEID_UNIT)
    {
        if (seatFlags & SEAT_FLAG_CAN_CONTROL)
        {
            passenger->SetCharm(NULL);
            pVehicle->SetCharmerGuid(ObjectGuid());
        }


        ((Creature*)passenger)->AI()->SetCombatMovement(true, true);
        if (!passenger->getVictim())
            passenger->GetMotionMaster()->Initialize();
    }
}
