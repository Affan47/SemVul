getURLEncodedVars(as_object& o)
{
    SortedPropertyList props = enumerateProperties(o);

    std::string data;
    string_table& st = getStringTable(o);

    for (SortedPropertyList::const_reverse_iterator i = props.rbegin(),
            e = props.rend(); i != e; ++i) {

        const std::string& name = i->first.toString(st);
        const std::string& value = i->second.to_string();


        if (!name.empty() && name[0] == '$') continue;

        URL::encode(value);
        if (i != props.rbegin()) data += '&';

        data += name + "=" + value;

    }
    return data;
}
