parse(const string &command, const string &args,
                                bool trusted) {

    typedef std::vector<string> StringTokens;
    StringTokens tokens;
    FbTk::StringUtil::stringtok<StringTokens>(tokens, args);

    if (tokens.size() < 1) {
        return 0;
    }

    int dx, dy;
    bool is_relative_x = false, is_relative_y = false, ignore_x = false, ignore_y = false;

    if (command == "resizehorizontal") {
        parseToken(tokens[0], dx, is_relative_x, ignore_x);
        dy = 0;
    } else if (command == "resizevertical") {
        parseToken(tokens[0], dy, is_relative_y, ignore_y);
        dx = 0;
    } else {
        if (tokens.size() < 2) {
            return 0;
        }
        parseToken(tokens[0], dx, is_relative_x, ignore_x);
        parseToken(tokens[1], dy, is_relative_y, ignore_y);
    }

    if (command == "resizeto") {
        return new ResizeToCmd(dx, dy, is_relative_x, is_relative_y);
    }
    return new ResizeCmd(dx, dy, is_relative_x, is_relative_y);
}
