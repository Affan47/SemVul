RemovePlayer(Player* plr, ObjectGuid guid)
{

    if (IsFlagPickedUp())
    {
        if (m_flagCarrier == guid)
        {
            if (plr)
                EventPlayerDroppedFlag(plr);
            else
            {
                ClearFlagCarrier();
                RespawnFlag();
            }
        }
    }
}
