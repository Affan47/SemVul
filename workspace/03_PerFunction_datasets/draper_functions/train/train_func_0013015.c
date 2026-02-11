parseLogicCommand(const string &command, const string &args,
                               bool trusted) {
    if (command == "not") {
        Command<bool> *boolcmd =
                CommandParser<bool>::instance().parse(args, trusted);
        if (!boolcmd)
            return 0;
        RefCount<Command<bool> > ref(boolcmd);
        return new NotCommand(ref);
    } else if (command == "and")
        return addCommands<AndCommand>(new AndCommand(), args, trusted);
    else if (command == "or")
        return addCommands<OrCommand>(new OrCommand(), args, trusted);
    else if (command == "xor")
        return addCommands<XorCommand>(new XorCommand(), args, trusted);
    return 0;
}
