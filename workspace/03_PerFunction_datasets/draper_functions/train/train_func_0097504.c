handleRead(int rpipe, unsigned int &result)
{
    char type = 0;
    if (read(rpipe, &type, 1) <= 0) {
        if (errno == EAGAIN)
            return 0;

        return -1;
    }

    if (type != REPORT_OUT && type != REPORT_ERROR && type != REPORT_INFO && type != CHILD_END) {
        std::cerr << "#### You found a bug from cppcheck.\nThreadExecutor::handleRead error, type was:" << type << std::endl;
        std::exit(0);
    }

    unsigned int len = 0;
    if (read(rpipe, &len, sizeof(len)) <= 0) {
        std::cerr << "#### You found a bug from cppcheck.\nThreadExecutor::handleRead error, type was:" << type << std::endl;
        std::exit(0);
    }

    char *buf = new char[len];
    if (read(rpipe, buf, len) <= 0) {
        std::cerr << "#### You found a bug from cppcheck.\nThreadExecutor::handleRead error, type was:" << type << std::endl;
        std::exit(0);
    }

    if (type == REPORT_OUT) {
        _errorLogger.reportOut(buf);
    } else if (type == REPORT_ERROR || type == REPORT_INFO) {
        ErrorLogger::ErrorMessage msg;
        msg.deserialize(buf);

        std::string file;
        unsigned int line(0);
        if (!msg._callStack.empty()) {
            file = msg._callStack.back().getfile(false);
            line = msg._callStack.back().line;
        }

        if (!_settings.nomsg.isSuppressed(msg._id, file, line)) {

            std::string errmsg = msg.toString(_settings._verbose);
            if (std::find(_errorList.begin(), _errorList.end(), errmsg) == _errorList.end()) {
                _errorList.push_back(errmsg);
                if (type == REPORT_ERROR)
                    _errorLogger.reportErr(msg);
                else
                    _errorLogger.reportInfo(msg);
            }
        }
    } else if (type == CHILD_END) {
        std::istringstream iss(buf);
        unsigned int fileResult = 0;
        iss >> fileResult;
        result += fileResult;
        delete [] buf;
        return -1;
    }

    delete [] buf;
    return 1;
}
