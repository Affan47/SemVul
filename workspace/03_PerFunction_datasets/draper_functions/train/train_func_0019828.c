fnt_s_new(obj, name)
    VALUE obj;
    struct RString *name;
{
    Check_Type(name, T_STRING);
    return fnt_new(RSTRING_PTR(name));
}
