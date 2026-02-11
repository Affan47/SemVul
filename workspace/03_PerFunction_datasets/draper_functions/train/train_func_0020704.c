operator==(const BidiContext& c1, const BidiContext& c2)
{
    if (&c1 == &c2)
        return true;
    if (c1.level != c2.level || c1.override != c2.override || c1.dir != c2.dir || c1.basicDir != c2.basicDir)
        return false;
    if (!c1.parent)
        return !c2.parent;
    return c2.parent && *c1.parent == *c2.parent;
}
