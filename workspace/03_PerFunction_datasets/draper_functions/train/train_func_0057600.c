write_super_block(void) {


	Super.s_state |= MINIX_VALID_FS;
	if ( errors_uncorrected )
		Super.s_state |= MINIX_ERROR_FS;
	else
		Super.s_state &= ~MINIX_ERROR_FS;

	if (MINIX_BLOCK_SIZE != lseek(IN, MINIX_BLOCK_SIZE, SEEK_SET))
		die(_("seek failed in write_super_block"));
	if (MINIX_BLOCK_SIZE != write(IN, super_block_buffer, MINIX_BLOCK_SIZE))
		die(_("unable to write super-block"));

	return;
}
