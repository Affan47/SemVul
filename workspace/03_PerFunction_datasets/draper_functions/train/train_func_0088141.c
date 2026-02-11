leakIfAllocated(const Token *vartok,
                                       const VarInfo &varInfo)
{
    const std::map<unsigned int, std::string> &alloctype = varInfo.alloctype;
    const std::map<unsigned int, std::string> &possibleUsage = varInfo.possibleUsage;

    const std::map<unsigned int,std::string>::const_iterator var = alloctype.find(vartok->varId());
    if (var != alloctype.end() && var->second != "dealloc") {
        const std::map<unsigned int, std::string>::const_iterator use = possibleUsage.find(vartok->varId());
        if (use == possibleUsage.end()) {
            leakError(vartok, vartok->str());
        } else {
            configurationInfo(vartok, use->second);
        }
    }
}
