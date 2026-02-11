dsgw_emitq (FILE* f, const char* s, size_t n)
{
    if (f == stdout && quotation_depth > 0) {
	return dsgw_emitr (quotation_depth, s, n);
    }
    return dsgw_fputn (f, s, n);
}
