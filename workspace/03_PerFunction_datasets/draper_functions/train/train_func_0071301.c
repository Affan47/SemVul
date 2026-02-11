mangle(const string& s, const Node* np, string& newName)
{
    const char** namep = np->names;
    while(*namep)
    {
        if(ciEquals(s, *namep))
        {
            newName = manglePrefix + s + mangleSuffix;
            return true;
        }
        ++namep;
    }
    const Node** parentp = np->parents;
    while(*parentp)
    {
        if(mangle(s, *parentp, newName))
        {
            return true;
        }
        ++parentp;
    }
    return false;
}
