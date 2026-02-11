make_template_array_module(Ya_template *ya_templ, const int level,
                           memory_kind kind, IntSet funcset, IntSet subrset)
{
    Module_table *m;
    IntSet target;

    if (!cmp_static_global_assign_array) {
        return ;
    }
    for (m = module_head; m != NULL; m = m->next) {
        if (m->kind == MODULE_FUNC) {
            target = funcset;
        } else if (m->kind == MODULE_SUB) {
            target = subrset;
        } else {
            target = NULL;
        }
        if (target != NULL
            && in_IntSet(target, m->entry)) {
            get_template_array_table(m, ya_templ, level, kind);
        }
    }
}
