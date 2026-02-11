property(const char *name, PURE purity)
{
    switch (purity)
    {
        case PUREimpure:


            break;
        case PUREweak:
            property(name, "weak");
            break;
        case PUREconst:
            property(name, "const");
            break;
        case PUREstrong:
            property(name, "strong");
            break;
        case PUREfwdref:
            property(name, "fwdref");
            break;
        default:
            assert(false);
    }
}
