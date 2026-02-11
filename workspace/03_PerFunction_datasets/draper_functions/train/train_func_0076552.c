setRights(const char *roleName, const Core::IUser::UserRights rights)
{
    Core::IUser::UserRights r = rights;
    if (rights & Core::IUser::ReadAll)
        r |= Core::IUser::ReadOwn | Core::IUser::ReadDelegates;
    if (rights & Core::IUser::WriteAll)
        r |= Core::IUser::WriteOwn | Core::IUser::WriteDelegates;
    d->m_Role_Rights[roleName].insert(RIGHTS_RIGHTS, int(r));
    if (!d->m_ModifiedRoles.contains(roleName))
        d->m_ModifiedRoles.insert(roleName);
    d->m_IsNull = false;
    setModified(true);
}
