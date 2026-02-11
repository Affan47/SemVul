copy_dtu_array_info(Dtu_array_info *daipt)
{
    Dtu_array_info *ndaipt = NULL;

    if (daipt != NULL) {
	ndaipt = alloc_dtu_array_info();
	ndaipt->opt = alloc_operand();
	ndaipt->opt->entry = daipt->opt->entry;
	ndaipt->opt->kind = daipt->opt->kind;
	ndaipt->mt_no = daipt->mt_no;
	ndaipt->pe_no = daipt->pe_no;
	ndaipt->type = daipt->type;
	ndaipt->offset = semtree_dup(daipt->offset);
	ndaipt->size = semtree_dup(daipt->size);
	ndaipt->stride = semtree_dup(daipt->stride);
	ndaipt->number = semtree_dup(daipt->number);
    }

    return ndaipt;
}
