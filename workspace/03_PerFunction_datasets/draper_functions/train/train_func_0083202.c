HrefToCommand(const wxString& href, wxString& args)
{
    if (!href.StartsWith(commandTag, &args))
        return cmdNone;

    size_t separator = args.rfind(separatorTag);
    if (separator == wxString::npos)
        separator = args.size() + 1;

    long int command;
    bool gotCommand = args.SubString(0,separator-1).ToLong(&command);
    if (!gotCommand)
        return cmdNone;

    if (separator + 1 < args.size())
        args = args.SubString(separator+1, args.size());
    else
        args.clear();

    return (Command)(command);
}
