printMsg_(Verbosity level, const format & f)
{
    checkInterrupt();
    if (level > verbosity) return;
    string prefix;
    if (logType == ltPretty)
        for (int i = 0; i < nestingLevel; i++)
            prefix += "|   ";
    else if (logType == ltEscapes && level != lvlInfo)
        prefix = "\033[" + escVerbosity(level) + "s";
    string s = (format("%1%%2%\n") % prefix % f.str()).str();
    writeToStderr((const unsigned char *) s.c_str(), s.size());
}
