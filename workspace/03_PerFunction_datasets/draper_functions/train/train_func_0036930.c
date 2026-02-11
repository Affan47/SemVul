set_str_var_by_namehash(const char *name, unsigned int hash,
    conString *value, int exportflag)
{
    Var *var = hfindglobalvar(name, hash);
    return setstrvar(var ? var : newglobalvar(name), value,
	exportflag);
}
