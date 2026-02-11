operator+=(const tString &s)
{
    if (Len() > 0 && operator()(Len()-1) == 0)
        SetLen(Len()-1);

    for (int i = 0; i< s.Len(); i++)
        operator[](Len()) = s(i);

    if (Len() > 0 && operator()(Len()-1) != 0)
        operator[](Len()) = 0;

    return *this;
}
