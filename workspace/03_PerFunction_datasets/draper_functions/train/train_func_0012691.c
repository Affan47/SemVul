update_relation_in_statement(Module_table *new, Statement *stm)
{
    Quadruple *current = NULL;

    for (current = stm->qr_head; current; current = current->next) {
	update_relation_in_quadruple(new, current);
    }
}
