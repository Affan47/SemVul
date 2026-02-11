TOString(SubString const  & a)
{
    return new string(a.s->substr(a.i,a.n));
}
