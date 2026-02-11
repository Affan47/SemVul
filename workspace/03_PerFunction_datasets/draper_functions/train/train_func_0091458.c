set_templ_array_rev_exc_local_for_arg(IntSet callee_templ,
                                      IntSet caller_templ,
                                      IntSet local_array,
                                      Operand *real_head,
                                      Operand *dummy_head)
{
    Operand *real, *dummy;
    for (real = real_head, dummy = dummy_head;
         real != NULL && dummy != NULL;
         real = real->next, dummy = dummy->next) {
        if (real->kind == KIND_ARRAY && dummy->kind == KIND_ARRAY
            && in_IntSet(callee_templ, dummy->tbl.a->entry)
            && !in_IntSet(local_array, real->tbl.a->entry)) {
            add1_IntSet(caller_templ, real->tbl.a->entry);
        }
    }
}
