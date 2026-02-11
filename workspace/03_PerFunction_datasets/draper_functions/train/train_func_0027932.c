operator=(PList::Dictionary& d)
{
    for (Dictionary::iterator it = _map.begin(); it != _map.end(); it++)
    {
        plist_free(it->second->GetPlist());
        delete it->second;
    }
    _map.clear();

    _node = plist_copy(d.GetPlist());
    plist_dict_iter it = NULL;

    char* key = NULL;
    plist_t subnode = NULL;
    plist_dict_new_iter(_node, &it);
    plist_dict_next_item(_node, it, &key, &subnode);
    while (subnode)
    {
        _map[std::string(key)] = Node::FromPlist(subnode, this);

        subnode = NULL;
        free(key);
        key = NULL;
        plist_dict_next_item(_node, it, NULL, &subnode);
    }
    free(it);
    return *this;
}
