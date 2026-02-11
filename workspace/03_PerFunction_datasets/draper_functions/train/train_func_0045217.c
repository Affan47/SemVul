HandleGoTaxinodeCommand(char* args)
{
    Player* _player = m_session->GetPlayer();

    uint32 nodeId;
    if (!ExtractUint32KeyFromLink(&args, "Htaxinode", nodeId))
        return false;

    TaxiNodesEntry const* node = sTaxiNodesStore.LookupEntry(nodeId);
    if (!node)
    {
        PSendSysMessage(LANG_COMMAND_GOTAXINODENOTFOUND, nodeId);
        SetSentErrorMessage(true);
        return false;
    }

    if (node->x == 0.0f && node->y == 0.0f && node->z == 0.0f)
    {
        PSendSysMessage(LANG_INVALID_TARGET_COORD, node->x, node->y, node->map_id);
        SetSentErrorMessage(true);
        return false;
    }

    return HandleGoHelper(_player, node->map_id, node->x, node->y, &node->z);
}
