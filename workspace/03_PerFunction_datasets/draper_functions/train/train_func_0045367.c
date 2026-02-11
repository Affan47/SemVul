bofm_locate_section ( userptr_t bofmtab, size_t len,
				    uint32_t magic,
				    struct bofm_section_header *bofmsec ) {
	size_t offset = sizeof ( struct bofm_global_header );

	while ( offset < len ) {
		copy_from_user ( bofmsec, bofmtab, offset,
				 sizeof ( *bofmsec ) );
		if ( bofmsec->magic == magic )
			return offset;
		if ( bofmsec->magic == BOFM_DONE_MAGIC )
			break;
		offset += ( sizeof ( *bofmsec ) + bofmsec->length );
	}
	return 0;
}
