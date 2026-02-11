updateUserPreferences()
{
    if (WarnAllProcesses)
        qWarning() << Q_FUNC_INFO;
    d->checkNullUser();
    if (!d->m_CurrentUserUuid.isEmpty() && d->m_CurrentUserUuid!=::SERVER_ADMINISTRATOR_UUID) {

        Internal::UserData *user = d->m_Uuid_UserList.value(d->m_CurrentUserUuid, 0);
        if (user) {
            user->setPreferences(settings()->userSettings());
            userBase()->saveUserPreferences(user->uuid(), settings()->userSettings());
            if (user->hasModifiedDynamicDataToStore()) {

                userBase()->savePapers(user);
            }
        } else {
            LOG_ERROR("No user uuid");
        }
    }
}
