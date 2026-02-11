readAliases(unsigned int varid, const Token* tok)
{
    VariableUsage *usage = find(varid);

    if (usage) {
        std::set<unsigned int>::iterator aliases;

        for (aliases = usage->_aliases.begin(); aliases != usage->_aliases.end(); ++aliases) {
            VariableUsage *aliased = find(*aliases);

            if (aliased) {
                _varReadInScope.back().insert(*aliases);
                aliased->_read = true;
                aliased->_lastAccess = tok;
            }
        }
    }
}
