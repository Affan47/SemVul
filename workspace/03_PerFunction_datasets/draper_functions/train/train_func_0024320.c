luUpgradeMerge(enum usage_level ul, const char *command)
{
    int is_my_command = (command && 0 == strcmp(command, "upgrade-merge"));
    if (ul == usage_all || !command || is_my_command)
    FPS "%-15s Upgrade an old database and merge it into a new one\n",
        "--upgrade-merge");
    if (ul == usage_selected && !is_my_command)
        return;
    FPS "%-20s Cert database directory to merge into (default is ~/.netscape)\n",
        "   -d certdir");
    FPS "%-20s Cert & Key database prefix of the target database\n",
        "   -P dbprefix");
    FPS "%-20s Specify the password file for the target database\n",
        "   -f pwfile");
    FPS "%-20s \n%-20s Cert database directory to upgrade from\n",
        "   --source-dir certdir", "");
    FPS "%-20s \n%-20s Cert & Key database prefix of the upgrade database\n",
        "   --source-prefix dbprefix", "");
    FPS "%-20s \n%-20s Unique identifier for the upgrade database\n",
        "   --upgrade-id uniqueID", "");
    FPS "%-20s \n%-20s Name of the token while it is in upgrade state\n",
        "   --upgrade-token-name name", "");
    FPS "%-20s Specify the password file for the upgrade database\n",
        "   -@ pwfile");
    FPS "\n");
}
