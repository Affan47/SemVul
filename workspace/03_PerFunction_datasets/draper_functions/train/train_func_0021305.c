show_type(jl_value_t *t)
{
    ios_t *s = jl_current_output_stream();
    if (jl_is_func_type(t)) {
        if (t == (jl_value_t*)jl_any_func) {
            ios_puts("Function", s);
        }
        else {
            jl_show((jl_value_t*)((jl_func_type_t*)t)->from);
            ios_write(s, "-->", 3);
            jl_show((jl_value_t*)((jl_func_type_t*)t)->to);
        }
    }
    else if (t == (jl_value_t*)jl_function_type) {
        ios_puts("Function", s);
    }
    else if (jl_is_union_type(t)) {
        if (t == (jl_value_t*)jl_bottom_type) {
            ios_write(s, "None", 4);
        }
        else if (t == jl_top_type) {
            ios_write(s, "Top", 3);
        }
        else {
            ios_write(s, "Union", 5);
            show_tuple(((jl_uniontype_t*)t)->types, '(', ')', 0);
        }
    }
    else if (jl_is_seq_type(t)) {
        jl_show(jl_tparam0(t));
        ios_write(s, "...", 3);
    }
    else if (jl_is_typector(t)) {
        jl_show((jl_value_t*)((jl_typector_t*)t)->body);
    }
    else {
        assert(jl_is_some_tag_type(t));
        jl_tag_type_t *tt = (jl_tag_type_t*)t;
        ios_puts(tt->name->name->name, s);
        jl_tuple_t *p = tt->parameters;
        if (p->length > 0)
            show_tuple(p, '{', '}', 0);
    }
}
