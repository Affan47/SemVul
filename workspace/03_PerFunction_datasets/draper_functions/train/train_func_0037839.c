GetGameObjectWithGuid(uint32 lowguid, uint32 entry)
{
    if (!m_session)
        { return NULL; }

    Player* pl = m_session->GetPlayer();

    return pl->GetMap()->GetGameObject(ObjectGuid(HIGHGUID_GAMEOBJECT, entry, lowguid));
}
