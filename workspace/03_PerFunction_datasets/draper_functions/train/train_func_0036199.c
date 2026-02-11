KickPlayer(ObjectGuid guid)
{
    if (Player* p = ObjectAccessor::FindPlayer(guid, false))
    {
        WorldSession* s = p->GetSession();
        s->KickPlayer();
        s->LogoutPlayer(false);
    }
}
