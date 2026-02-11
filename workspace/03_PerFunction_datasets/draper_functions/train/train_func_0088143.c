ReadAddonsInfo(WorldPacket& data)
{
    if (data.rpos() + 4 > data.size())
        return;
    uint32 size;
    data >> size;

    if (!size)
        return;

    if (size > 0xFFFFF)
    {
        sLog.outError("WorldSession::ReadAddonsInfo addon info too big, size %u", size);
        return;
    }

    uLongf uSize = size;

    uint32 pos = data.rpos();

    ByteBuffer addonInfo;
    addonInfo.resize(size);

    if (uncompress(const_cast<uint8*>(addonInfo.contents()), &uSize, const_cast<uint8*>(data.contents() + pos), data.size() - pos) == Z_OK)
    {
        uint32 addonsCount;
        addonInfo >> addonsCount;

        for (uint32 i = 0; i < addonsCount; ++i)
        {
            std::string addonName;
            uint8 enabled;
            uint32 crc, unk1;


            if (addonInfo.rpos() + 1 > addonInfo.size())
                return;

            addonInfo >> addonName;

            addonInfo >> enabled >> crc >> unk1;

            DEBUG_LOG("ADDON: Name: %s, Enabled: 0x%x, CRC: 0x%x, Unknown2: 0x%x", addonName.c_str(), enabled, crc, unk1);

            m_addonsList.push_back(AddonInfo(addonName, enabled, crc));
        }

        uint32 unk2;
        addonInfo >> unk2;

        if (addonInfo.rpos() != addonInfo.size())
            DEBUG_LOG("packet under read!");
    }
    else
        sLog.outError("Addon packet uncompress error!");
}
