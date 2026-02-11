parseIntCmd(const string &command, const string &args,
                           bool trusted) {
    int num = 1;
    FbTk_istringstream iss(args.c_str());
    iss >> num;
    if (command == "nextworkspace")
        return new NextWorkspaceCmd(num);
    else if (command == "prevworkspace")
        return new PrevWorkspaceCmd(num);
    else if (command == "rightworkspace")
        return new RightWorkspaceCmd(num);
    else if (command == "leftworkspace")
        return new LeftWorkspaceCmd(num);
    else if (command == "workspace")

        return new JumpToWorkspaceCmd(num - 1);
    return 0;
}
