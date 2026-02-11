m_and(li_object *seq, li_object *env) {
    for (; seq && li_cdr(seq); seq = li_cdr(seq))
        if (li_not(li_eval(li_car(seq), env)))
            return li_false;
    if (!seq)
        return li_true;
    return li_car(seq);
}
