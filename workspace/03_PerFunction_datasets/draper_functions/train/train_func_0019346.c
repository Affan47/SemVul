shrink_callee_arg_head(Shrink_args *sa)
{
    Operand *formal, *formal_prev = NULL;
    int nth_formal;

    for (nth_formal = 0, formal = sa->callee_module->arg_head;
         nth_formal < sa->arg_num && formal != NULL;
         nth_formal++) {

        if (in_IntSet(sa->remove_set, nth_formal)) {
            if (formal_prev != NULL)
                formal_prev->next = formal->next;
            else
                sa->callee_module->arg_head = formal->next;

            formal = formal->next;
            continue;
        }

        formal_prev = formal;
        formal = formal->next;
    }

    formal_prev->next = NULL;
}
