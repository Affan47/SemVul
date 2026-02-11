select_locals(Lsymtab *sym_entry)
#else
select_locals(sym_entry)
    Lsymtab *sym_entry;
#endif
{


    if (EXCL_SF3_DECLARATIONS() && sf3_internal_name(sym_entry))
	return (0);
    else if (sym_entry->argument ||
	sym_entry->common_var ||
	sym_entry->declared_external ||
	sym_entry->declared_intrinsic ||
	sym_entry->entry_point ||
	sym_entry->external ||
	sym_entry->intrinsic ||
	sym_entry->invoked_as_func ||
	sym_entry->parameter)
	return (0);
    else
	return (1);
}
