cb_userAdded(LightDMUserList *user_list, LightDMUser *ldmUser, gpointer data)
{
    Q_UNUSED(user_list)
    UsersModelPrivate *that = static_cast<UsersModelPrivate*>(data);

    that->q_func()->beginInsertRows(QModelIndex(), that->users.size(), that->users.size());

    UserItem user;
    user.name = QString::fromUtf8(lightdm_user_get_name(ldmUser));
    user.homeDirectory = QString::fromUtf8(lightdm_user_get_home_directory(ldmUser));
    user.realName = QString::fromUtf8(lightdm_user_get_real_name(ldmUser));
    user.image = QString::fromUtf8(lightdm_user_get_image(ldmUser));
    user.background = QString::fromUtf8(lightdm_user_get_background(ldmUser));
    user.isLoggedIn = lightdm_user_get_logged_in(ldmUser);
    user.hasMessages = lightdm_user_get_has_messages(ldmUser);
    user.uid = (quint64)lightdm_user_get_uid(ldmUser);
    that->users.append(user);

    that->q_func()->endInsertRows();

}
