uninitdataError(const Token *tok, const std::string &varname)
{
    reportError(tok, Severity::error, "uninitdata", "Data is allocated but not initialized: " + varname);
}
