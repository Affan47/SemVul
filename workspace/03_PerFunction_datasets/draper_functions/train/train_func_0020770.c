memory_protection_error(CELL addr, F_STACK_FRAME *native_stack)
{
	if(in_page(addr, ds_bot, 0, -1))
		general_error(ERROR_DS_UNDERFLOW,F,F,native_stack);
	else if(in_page(addr, ds_bot, ds_size, 0))
		general_error(ERROR_DS_OVERFLOW,F,F,native_stack);
	else if(in_page(addr, rs_bot, 0, -1))
		general_error(ERROR_RS_UNDERFLOW,F,F,native_stack);
	else if(in_page(addr, rs_bot, rs_size, 0))
		general_error(ERROR_RS_OVERFLOW,F,F,native_stack);
	else if(in_page(addr, nursery->end, 0, 0))
		critical_error("allot_object() missed GC check",0);
	else if(in_page(addr, gc_locals_region->start, 0, -1))
		critical_error("gc locals underflow",0);
	else if(in_page(addr, gc_locals_region->end, 0, 0))
		critical_error("gc locals overflow",0);
	else if(in_page(addr, extra_roots_region->start, 0, -1))
		critical_error("extra roots underflow",0);
	else if(in_page(addr, extra_roots_region->end, 0, 0))
		critical_error("extra roots overflow",0);
	else
		general_error(ERROR_MEMORY,allot_cell(addr),F,native_stack);
}
