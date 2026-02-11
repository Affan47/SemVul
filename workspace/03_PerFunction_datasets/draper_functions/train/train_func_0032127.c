FillMessageData(WorldPacket* data, WorldSession* session, uint8 type, uint32 language, const char* channelName, ObjectGuid targetGuid, const char* message, Unit* speaker)
{
    uint32 messageLength = (message ? strlen(message) : 0) + 1;

    data->Initialize(SMSG_MESSAGECHAT, 100);
    *data << uint8(type);
    if ((type != CHAT_MSG_CHANNEL && type != CHAT_MSG_WHISPER) || language == LANG_ADDON)
        *data << uint32(language);
    else
        *data << uint32(LANG_UNIVERSAL);

    switch (type)
    {
        case CHAT_MSG_SAY:
        case CHAT_MSG_PARTY:
        case CHAT_MSG_PARTY_LEADER:
        case CHAT_MSG_RAID:
        case CHAT_MSG_GUILD:
        case CHAT_MSG_OFFICER:
        case CHAT_MSG_YELL:
        case CHAT_MSG_WHISPER:
        case CHAT_MSG_CHANNEL:
        case CHAT_MSG_RAID_LEADER:
        case CHAT_MSG_RAID_WARNING:
        case CHAT_MSG_BG_SYSTEM_NEUTRAL:
        case CHAT_MSG_BG_SYSTEM_ALLIANCE:
        case CHAT_MSG_BG_SYSTEM_HORDE:
        case CHAT_MSG_BATTLEGROUND:
        case CHAT_MSG_BATTLEGROUND_LEADER:
            targetGuid = session ? session->GetPlayer()->GetObjectGuid() : ObjectGuid();
            break;
        case CHAT_MSG_MONSTER_SAY:
        case CHAT_MSG_MONSTER_PARTY:
        case CHAT_MSG_MONSTER_YELL:
        case CHAT_MSG_MONSTER_WHISPER:
        case CHAT_MSG_MONSTER_EMOTE:
        case CHAT_MSG_RAID_BOSS_WHISPER:
        case CHAT_MSG_RAID_BOSS_EMOTE:
        case CHAT_MSG_BATTLENET:
        {
            *data << ObjectGuid(speaker->GetObjectGuid());
            *data << uint32(0);
            *data << uint32(strlen(speaker->GetName()) + 1);
            *data << speaker->GetName();
            ObjectGuid listener_guid;
            *data << listener_guid;
            if (listener_guid && !listener_guid.IsPlayer())
            {
                *data << uint32(1);
                *data << uint8(0);
            }
            *data << uint32(messageLength);
            *data << message;
            *data << uint8(0);
            return;
        }
        default:
            if (type != CHAT_MSG_WHISPER_INFORM && type != CHAT_MSG_IGNORED && type != CHAT_MSG_DND && type != CHAT_MSG_AFK)
                targetGuid.Clear();
            break;
    }

    *data << ObjectGuid(targetGuid);
    *data << uint32(0);

    if (type == CHAT_MSG_CHANNEL)
    {
        MANGOS_ASSERT(channelName);
        *data << channelName;
    }

    *data << ObjectGuid(targetGuid);
    *data << uint32(messageLength);
    *data << message;
    if (session != 0 && type != CHAT_MSG_WHISPER_INFORM && type != CHAT_MSG_DND && type != CHAT_MSG_AFK)
        *data << uint8(session->GetPlayer()->GetChatTag());
    else
        *data << uint8(0);
}
