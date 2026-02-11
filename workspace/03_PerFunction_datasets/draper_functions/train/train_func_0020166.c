InsertMaterial(const string& name)
{
    int i;
    Material m(&paths_to_materials);
    m.ReadItself(name);
    i = materials.size();
    materials.push_back(m);
    index.insert(make_pair(name, i));
    return i;
}
