HandleTaxiQueryAvailableNodes(WorldPacket& recv_data)
{
    DEBUG_LOG("WORLD: Received opcode CMSG_TAXIQUERYAVAILABLENODES");

    ObjectGuid guid;
    recv_data >> guid;


    Creature* unit = GetPlayer()->GetNPCIfCanInteractWith(guid, UNIT_NPC_FLAG_FLIGHTMASTER);
    if (!unit)
    {
        DEBUG_LOG("WORLD: HandleTaxiQueryAvailableNodes - %s not found or you can't interact with him.", guid.GetString().c_str());
        return;
    }


    if (GetPlayer()->hasUnitState(UNIT_STAT_DIED))
        { GetPlayer()->RemoveSpellsCausingAura(SPELL_AURA_FEIGN_DEATH); }


    if (SendLearnNewTaxiNode(unit))
        { return; }


    SendTaxiMenu(unit);
}
