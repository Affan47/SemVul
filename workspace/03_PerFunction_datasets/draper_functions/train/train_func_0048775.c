is_des_p(const char *name)
{
    int len = strlen(name);
    return len > 1 && name[0] == '[' && name[len-1] == ']';
}
