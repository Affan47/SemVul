Process(WorldPacket* packet)
{
    OpcodeHandler const& opHandle = opcodeTable[packet->GetOpcode()];
    if (opHandle.packetProcessing == PROCESS_INPLACE)
        { return true; }


    return MapSessionFilterHelper(m_pSession, opHandle);
}
