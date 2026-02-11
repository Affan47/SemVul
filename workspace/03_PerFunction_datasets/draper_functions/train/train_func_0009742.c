m_do(li_object *seq, li_object *env) {
    li_object *binding;
    li_object *head;
    li_object *iter;
    li_object *let_args;
    li_object *let_bindings;
    li_object *tail;

    LI_UNUSED_VARIABLE(env);
    assert_pair(seq);
    assert_pair(li_cdr(seq));
    head = tail = li_cons(li_symbol("let"), li_null);
    tail = li_set_cdr(tail, li_cons(li_symbol("#"), li_null));
    let_args = li_null;
    let_bindings = li_null;
    for (iter = li_car(seq); iter; iter = li_cdr(iter)) {
        binding = li_car(iter);
        assert_pair(binding);
        assert_pair(li_cdr(binding));
        assert_symbol(li_car(binding));
        if (li_cddr(binding)) {
            let_args = li_cons(li_caddr(binding), let_args);
            binding = li_cons(li_car(binding), li_cons(li_cadr(binding), li_null));
        } else {
            let_args = li_cons(li_car(binding), let_args);
        }
        let_bindings = li_cons(binding, let_bindings);
    }
    tail = li_set_cdr(tail, li_cons(let_bindings, li_null));
    tail = li_set_cdr(tail, li_cons(li_null, li_null));
    tail = li_set_car(tail, li_cons(li_symbol("cond"), li_null));
    tail = li_set_cdr(tail, li_cons(li_cadr(seq), li_null));
    tail = li_set_cdr(tail, li_cons(li_null, li_null));
    tail = li_set_car(tail, li_cons(li_symbol("else"), li_null));
    for (iter = li_cddr(seq); iter; iter = li_cdr(iter))
        tail = li_set_cdr(tail, iter);
    tail = li_set_cdr(tail, li_cons(li_cons(li_symbol("#"), let_args), li_null));
    return head;
}
