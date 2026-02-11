use(unsigned int varid)
{
    VariableUsage *usage = find(varid);

    if (usage)
    {
        usage->use();

        std::set<unsigned int>::iterator aliases;

        for (aliases = usage->_aliases.begin(); aliases != usage->_aliases.end(); ++aliases)
        {
            VariableUsage *aliased = find(*aliases);

            if (aliased)
                aliased->use();
        }
    }
}
