modified(unsigned int varid, const Token* tok)
{
    VariableUsage *usage = find(varid);

    if (usage) {
        usage->_modified = true;
        usage->_lastAccess = tok;

        std::set<unsigned int>::iterator aliases;

        for (aliases = usage->_aliases.begin(); aliases != usage->_aliases.end(); ++aliases) {
            VariableUsage *aliased = find(*aliases);

            if (aliased) {
                aliased->_modified = true;
                aliased->_lastAccess = tok;
            }
        }
    }
}
