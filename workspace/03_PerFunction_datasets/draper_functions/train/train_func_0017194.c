LogoutPlayerBot(ObjectGuid guid)
{
    Player* bot = GetPlayerBot(guid);
    if (bot)
    {
        WorldSession * botWorldSessionPtr = bot->GetSession();
        m_playerBots.erase(guid);
        botWorldSessionPtr->LogoutPlayer(true);
        delete botWorldSessionPtr;
    }
}
