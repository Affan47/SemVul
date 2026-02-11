ShowHelpForCommand(ChatCommand* table, const char* cmd)
{
    char const* oldCmd = cmd;
    ChatCommand* command = NULL;
    ChatCommand* parentCommand = NULL;

    ChatCommand* showCommand = NULL;
    ChatCommand* childCommands = NULL;

    ChatCommandSearchResult res = FindCommand(table, cmd, command, &parentCommand);

    switch (res)
    {
        case CHAT_COMMAND_OK:
        {

            if (strlen(command->Name) == 0 && parentCommand)
            {
                showCommand = parentCommand;
                cmd = "";
            }
            else
                showCommand = command;

            childCommands = showCommand->ChildCommands;
            break;
        }
        case CHAT_COMMAND_UNKNOWN_SUBCOMMAND:
            showCommand = command;
            childCommands = showCommand->ChildCommands;
            break;
        case CHAT_COMMAND_UNKNOWN:

            childCommands = table != getCommandTable() || strlen(oldCmd) == 0 ? table : NULL;
            command = NULL;
            break;
    }

    if (command && !command->Help.empty())
        SendSysMessage(command->Help.c_str());

    if (childCommands)
        if (ShowHelpForSubCommands(childCommands, showCommand ? showCommand->Name : ""))
            return true;

    if (command && command->Help.empty())
        SendSysMessage(LANG_NO_HELP_CMD);

    return command || childCommands;
}
