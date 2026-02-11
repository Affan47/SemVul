fish_xdm_login_hack_hack_hack_hack(std::vector<std::string> *cmds, int argc, const char * const *argv)
{
    bool result = false;
    if (cmds && cmds->size() == 1)
    {
        const std::string &cmd = cmds->at(0);
        if (cmd == "exec \"${@}\"" || cmd == "exec \"$@\"")
        {

            std::string new_cmd = "exec";
            for (int i=1; i < argc; i++)
            {
                const char *arg = argv[i];
                if (arg)
                {
                    new_cmd.push_back(' ');
                    new_cmd.append(escape_single_quoted_hack_hack_hack_hack(arg));
                }
            }

            cmds->at(0) = new_cmd;
            result = true;
        }
    }
    return result;
}
