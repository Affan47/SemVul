is_valid_address(unsigned long addr, proc_t *proc) {

    if ( ((long)addr) & (sizeof(char *)-1) )
       return -1 ;

	 return !dbg_map_lookup_by_address(proc, addr, NULL);
}
