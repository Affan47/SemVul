setNonRepeatingOpt(const string& opt, const string& val)
{
    if(opt.empty())
    {
        return;
    }


    assert(_opts.find(opt) == _opts.end() || _validOpts.find(opt)->second->hasDefault);

    OValPtr ovp = new OptionValue;
    ovp->val = val;
    _opts[opt] = ovp;

    const string synonym = getSynonym(opt);
    if(!synonym.empty())
    {
        _opts[synonym] = ovp;
    }
}
