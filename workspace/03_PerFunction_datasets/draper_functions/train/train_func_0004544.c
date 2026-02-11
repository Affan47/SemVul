outWorldPacketDump(uint32 socket, uint32 opcode, char const* opcodeName, ByteBuffer const* packet, bool incoming)
{
    if (!worldLogfile)
        return;

    ACE_GUARD(ACE_Thread_Mutex, GuardObj, m_worldLogMtx);

    outTimestamp(worldLogfile);

    fprintf(worldLogfile, "\n%s:\nSOCKET: %u\nLENGTH: " SIZEFMTD "\nOPCODE: %s (0x%.4X)\nDATA:\n",
            incoming ? "CLIENT" : "SERVER",
            socket, packet->size(), opcodeName, opcode);

    size_t p = 0;
    while (p < packet->size())
    {
        for (size_t j = 0; j < 16 && p < packet->size(); ++j)
            fprintf(worldLogfile, "%.2X ", (*packet)[p++]);

        fprintf(worldLogfile, "\n");
    }

    fprintf(worldLogfile, "\n\n");
    fflush(worldLogfile);
}
