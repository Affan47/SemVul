operator=(const char* s)
{
    if (type == type_scalar)
        *u.str = s;
    else
    {
        deallocate();
        u.str = new std::string(s);
        type = type_scalar;
    }
    return *this;
}
