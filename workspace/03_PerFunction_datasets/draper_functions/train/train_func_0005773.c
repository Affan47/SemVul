cgcef_getarhdr(CGCEf *cgcef) {
    if (!cgcef) {
	return NULL;
    }
    cgcef_assert(cgcef->e_magic == CGCEF_MAGIC);
    if (cgcef->e_arhdr) {
	return cgcef->e_arhdr;
    }
    seterr(ERROR_NOTARCHIVE);
    return NULL;
}
