max_default(t_pd *x, t_symbol *s, int argc, t_atom *argv)
{
    int i;
    char str[80];
    startpost("%s: unknown message %s ", class_getname(pd_class(x)),
        s->s_name);
    for (i = 0; i < argc; i++)
    {
        atom_string(argv+i, str, 80);
        poststring(str);
    }
    endpost();
}
