AddLiteral(const char *x)
{
    tNEW(tOutputItem<tString>)(*this, tString(x));
}
