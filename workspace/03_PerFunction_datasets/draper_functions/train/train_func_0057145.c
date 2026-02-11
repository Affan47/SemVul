gc_init(TSRMLS_D)
{
	if (GC_G(buf) == NULL && GC_G(gc_enabled)) {
		GC_G(buf) = (gc_root_buffer*) malloc(sizeof(gc_root_buffer) * GC_ROOT_BUFFER_MAX_ENTRIES);
		GC_G(last_unused) = &GC_G(buf)[GC_ROOT_BUFFER_MAX_ENTRIES];
		gc_reset(TSRMLS_C);
	}
}
