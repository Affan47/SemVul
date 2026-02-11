eval_quasiquote(li_object *exp, li_object *env) {
    li_object *head, *iter, *tail;

    if (!li_is_pair(exp))
        return exp;
    else if (li_is_unquoted(exp))
        return li_eval(li_cadr(exp), env);
    else if (li_is_unquoted_splicing(li_car(exp))) {
        head = tail = li_null;
        for (iter = li_eval(li_cadar(exp), env); iter; iter = li_cdr(iter)) {
            if (head)
                tail = li_set_cdr(tail, li_cons(li_car(iter), li_null));
            else
                head = tail = li_cons(li_car(iter), li_null);
        }
        if (tail) {
            li_set_cdr(tail, eval_quasiquote(li_cdr(exp), env));
            return head;
        } else {
            return eval_quasiquote(li_cdr(exp), env);
        }
    }
    return li_cons(eval_quasiquote(li_car(exp), env),
            eval_quasiquote(li_cdr(exp), env));
}
