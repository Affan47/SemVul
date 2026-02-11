loadvars_tostring(const fn_call& fn)
{
	as_object* ptr = ensure<ValidThis>(fn);

	SortedPropertyList vars = enumerateProperties(*ptr);

    as_object* global = &getGlobal(*ptr);
    std::ostringstream o;

    const int ver = getSWFVersion(fn);
    string_table& st = getStringTable(fn);


	for (SortedPropertyList::const_reverse_iterator it = vars.rbegin(),
            itEnd = vars.rend(); it != itEnd; ++it) {

        if (it != vars.rbegin()) o << "&";
        const std::string& var =
            callMethod(global, NSV::PROP_ESCAPE, it->first.toString(st)).to_string();
        const std::string& val = callMethod(global, NSV::PROP_ESCAPE,
            it->second.to_string(ver)).to_string();
        o << var << "=" << val;
	}
    return as_value(o.str());
}
