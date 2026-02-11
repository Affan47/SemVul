resolveType(const string& type)
{
    if (types.find(type) != types.end())
        return types[type];
    else
        out.issueError("Unknown type:" + type);


    Type t;
    return t;
}
