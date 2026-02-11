init(FWObjectDatabase *root)
{
    Firewall::init(root);

    FWObject *state_sync_members = getFirstByType(StateSyncClusterGroup::TYPENAME);
    if (state_sync_members == NULL)
    {
        state_sync_members = root->create(StateSyncClusterGroup::TYPENAME);
        state_sync_members->setName("State Sync Group");
        state_sync_members->setStr("type", "conntrack");
        add(state_sync_members);
    }
}
