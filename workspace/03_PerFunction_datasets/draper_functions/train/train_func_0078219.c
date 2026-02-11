parse(const vector<string>& args,
        vector<string>& remaining_args) const
{
    remaining_args = vector<string>{};
    if (args.empty())
        throw OkShellException("ModeParser::parse, args is empty");
    else if (args.size() == 1)
    {
        return MainMode::EMPTY;
    }
    else if (args.size() == 2 && lowercase(args[1]) == "help")
    {

        return MainMode::HELP;
    }
    else if (lowercase(args[1]) == "ok")
    {
        remaining_args = vector<string>(args.begin() + 2, args.end());
        return MainMode::CONFIG;
    }
    else
    {
        remaining_args = vector<string>(args.begin() + 1, args.end());
        return MainMode::NORMAL;
    }
    return MainMode::ERROR;
}
