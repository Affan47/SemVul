deserialize(const std::string &data)
{
    _inconclusive = false;
    _callStack.clear();
    std::istringstream iss(data);
    std::vector<std::string> results;
    while (iss.good()) {
        unsigned int len = 0;
        if (!(iss >> len))
            return false;

        iss.get();
        std::string temp;
        for (unsigned int i = 0; i < len && iss.good(); ++i) {
            char c = static_cast<char>(iss.get());
            temp.append(1, c);
        }

        if (temp == "inconclusive") {
            _inconclusive = true;
            continue;
        }

        results.push_back(temp);
        if (results.size() == 4)
            break;
    }

    _id = results[0];
    _severity = Severity::fromString(results[1]);
    _shortMessage = results[2];
    _verboseMessage = results[3];

    unsigned int stackSize = 0;
    if (!(iss >> stackSize))
        return false;

    while (iss.good()) {
        unsigned int len = 0;
        if (!(iss >> len))
            return false;

        iss.get();
        std::string temp;
        for (unsigned int i = 0; i < len && iss.good(); ++i) {
            char c = static_cast<char>(iss.get());
            temp.append(1, c);
        }

        ErrorLogger::ErrorMessage::FileLocation loc;
        loc.setfile(temp.substr(temp.find(':') + 1));
        temp = temp.substr(0, temp.find(':'));
        std::istringstream fiss(temp);
        fiss >> loc.line;

        _callStack.push_back(loc);

        if (_callStack.size() >= stackSize)
            break;
    }

    return true;
}
