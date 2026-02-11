isAvailable(ChatCommand const& cmd) const
{

    if (!cmd.AllowConsole)
        return false;


    return GetAccessLevel() >= (AccountTypes)cmd.SecurityLevel;
}
