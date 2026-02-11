copy_operand_list_with_mpt(Module_table *mpt, Operand *head)
{
    Operand *oppt = NULL;
    Operand *new_oppt = NULL;
    Operand *new_head = NULL, *new_tail = NULL;

    for (oppt = head; oppt; oppt = oppt->next) {
	new_oppt = copy_operand_with_mpt(mpt, oppt);

	if (!new_head){
	    new_head = new_oppt;
	}else{
	    new_tail->next = new_oppt;
	}
	new_tail = new_oppt;
    }

    return(new_head);
}
