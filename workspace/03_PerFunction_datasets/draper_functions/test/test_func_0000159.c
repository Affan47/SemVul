isMain()
{
    return ident == Id::main &&
        linkage != LINKc && !isMember() && !isNested();
}
