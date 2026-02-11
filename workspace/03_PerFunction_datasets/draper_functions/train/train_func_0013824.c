jl_new_tagtype(jl_value_t *name, jl_tag_type_t *super,
                              jl_tuple_t *parameters)
{
    jl_typename_t *tn=NULL;
    JL_GC_PUSH(&tn);

    if (jl_is_typename(name))
        tn = (jl_typename_t*)name;
    else
        tn = jl_new_typename((jl_sym_t*)name);
    jl_tag_type_t *t = (jl_tag_type_t*)newobj((jl_type_t*)jl_tag_kind,
                                              TAG_TYPE_NW);
    t->name = tn;
    t->super = super;
    unbind_tvars(parameters);
    t->parameters = parameters;
    t->fptr = NULL;
    t->env = NULL;
    t->linfo = NULL;
    if (t->name->primary == NULL)
        t->name->primary = (jl_value_t*)t;
    JL_GC_POP();
    return t;
}
