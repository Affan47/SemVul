unseen(const std::string& eid)
{
    Entity* ent = getEntity(eid);
    if (!ent) return;

    ent->shutdown();
    delete ent;
}
