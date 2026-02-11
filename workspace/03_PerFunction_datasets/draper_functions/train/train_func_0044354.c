sib_decode( unsigned char *buf, size_t buf_len, x86_ea_t *ea,
			  unsigned int mod ) {


	size_t size = 1;
	struct SIB_byte sib;

	if ( buf_len < 1 ) {
		return 0;
	}

	byte_decode( *buf, (struct modRM_byte *)(void*)&sib );

	if ( sib.base == SIB_BASE_EBP && ! mod ) {


		imm32_signsized( &buf[1], buf_len, &ea->disp, sizeof(int32_t));
		ea->disp_size = sizeof(int32_t);
		ea->disp_sign = (ea->disp < 0) ? 1 : 0;
		size += 4;

	} else {

		ia32_handle_register( &ea->base, sib.base + 1 );
	}


	ea->scale = 1 << sib.scale;

	if (sib.index != SIB_INDEX_NONE) {

		ia32_handle_register( &ea->index, sib.index + 1 );
	}

	return (size);
}
