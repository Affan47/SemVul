getByTypeDeep(const string &type_name) const
{
    list<FWObject*> res = getByType(type_name);
    for (const_iterator i=begin(); i!=end(); ++i)
    {
        list<FWObject*> c_res = (*i)->getByTypeDeep(type_name);
        res.insert(res.end(), c_res.begin(), c_res.end());
    }
    return res;
}
