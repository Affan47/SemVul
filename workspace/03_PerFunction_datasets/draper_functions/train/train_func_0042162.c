mark_used_label_pestm(IntSet set, Pe_statement *pestm)
{
    Statement *s;

    for (s = pestm->stm_head; s != NULL; s = s->next) {
        Quadruple *q;
        if (s->ope != OPE_LABEL) {
            for (q = s->qr_head; q != NULL; q = q->next) {
                int i;
                for (i = 0; i < 4 && q->op[i] != NULL; i++) {
                    if (q->op[i]->kind == KIND_LABEL)
                        add1_IntSet(set, q->op[i]->entry);
                }
            }
        }
    }
}
