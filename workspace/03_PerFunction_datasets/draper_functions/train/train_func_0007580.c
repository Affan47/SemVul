operator[](UFName name) const
{
    _UFGroupMap::iterator iter = ufgroup->Map.find(name);
    if (iter == ufgroup->Map.end()) {
        Throw("No object with name '%s'", name);
    }
    return *ufgroup->Map[name];
}
