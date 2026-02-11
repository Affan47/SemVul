gatom_unescapit(t_symbol *s)
{
    if (*s->s_name == '-')
        return (gensym(s->s_name+1));
    else return (iemgui_raute2dollar(s));
}
