cgcef_getarsym(CGCEf *cgcef, size_t *ptr) {
    CGCEf_Arsym *syms;
    size_t count;
    size_t tmp;
    size_t i;
    char *s;
    char *e;

    if (!ptr) {
	ptr = &tmp;
    }
    *ptr = 0;
    if (!cgcef) {
	return NULL;
    }
    cgcef_assert(cgcef->e_magic == CGCEF_MAGIC);
    if (cgcef->e_kind != CGCEF_K_AR) {
	seterr(ERROR_NOTARCHIVE);
	return NULL;
    }
    if (cgcef->e_symtab && !cgcef->e_free_syms) {
	if (cgcef->e_symlen < 4) {
	    seterr(ERROR_SIZE_ARSYMTAB);
	    return NULL;
	}
	count = __load_u32M(cgcef->e_symtab);
	if (cgcef->e_symlen < 4 * (count + 1)) {
	    seterr(ERROR_SIZE_ARSYMTAB);
	    return NULL;
	}
	if (!(syms = (CGCEf_Arsym*)malloc((count + 1) * sizeof(*syms)))) {
	    seterr(ERROR_MEM_ARSYMTAB);
	    return NULL;
	}
	s = cgcef->e_symtab + 4 * (count + 1);
	e = cgcef->e_symtab + cgcef->e_symlen;
	for (i = 0; i < count; i++, s++) {
	    syms[i].as_name = s;
	    while (s < e && *s) {
		s++;
	    }
	    if (s >= e) {
		seterr(ERROR_SIZE_ARSYMTAB);
		free(syms);
		return NULL;
	    }
	    cgcef_assert(!*s);
	    syms[i].as_hash = cgcef_hash((unsigned char*)syms[i].as_name);
	    syms[i].as_off = __load_u32M(cgcef->e_symtab + 4 * (i + 1));
	}
	syms[count].as_name = NULL;
	syms[count].as_hash = ~0UL;
	syms[count].as_off = 0;
	cgcef->e_symtab = (char*)syms;
	cgcef->e_symlen = count + 1;
	cgcef->e_free_syms = 1;
    }
    *ptr = cgcef->e_symlen;
    return (CGCEf_Arsym*)cgcef->e_symtab;
}
