SendGlobalSysMessage(const char* str)
{

    WorldPacket data;


    char* buf = mangos_strdup(str);
    char* pos = buf;

    while (char* line = LineFromMessage(pos))
    {
        ChatHandler::BuildChatPacket(data, CHAT_MSG_SYSTEM, line, LANG_UNIVERSAL, CHAT_TAG_NONE, m_session->GetPlayer()->GetObjectGuid());
        sWorld.SendGlobalMessage(&data);
    }

    delete[] buf;
}
