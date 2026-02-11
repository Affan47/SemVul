checkUserRights()
{
    Core::IUser::UserRights r(userModel()->currentUserData(Core::IUser::ManagerRights).toInt());
    return r & Core::IUser::Create;
}
