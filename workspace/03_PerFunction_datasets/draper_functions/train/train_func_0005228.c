new_filter_subgroup(char *name, struct filter *list)
{
    struct filter *f;
    if ((f = __new_filter(F_SUBGROUP))) {
	f->u.sub.name = name;
	f->u.sub.list = list;
    }
    return f;
}
