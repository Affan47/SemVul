possibleUsageAll(const std::string &functionName)
{
    possibleUsage.clear();
    std::map<unsigned int, std::string>::const_iterator it;
    for (it = alloctype.begin(); it != alloctype.end(); ++it)
        possibleUsage[it->first] = functionName;
}
