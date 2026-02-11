elf_load_segment ( struct image *image, Elf_Phdr *phdr,
			      Elf_Ehdr *ehdr ) {
	physaddr_t dest;
	userptr_t buffer;
	unsigned long e_offset;
	int rc;


	if ( phdr->p_type != PT_LOAD )
		return 0;


	if ( ( phdr->p_offset + phdr->p_filesz ) > image->len ) {
		DBGC ( image, "ELF %p segment outside image\n", image );
		return -ENOEXEC;
	}


	dest = phdr->p_paddr;
	if ( ! dest )
		dest = phdr->p_vaddr;
	if ( ! dest ) {
		DBGC ( image, "ELF %p segment loads to physical address 0\n",
		       image );
		return -ENOEXEC;
	}
	buffer = phys_to_user ( dest );

	DBGC ( image, "ELF %p loading segment [%x,%x) to [%x,%x,%x)\n", image,
	       phdr->p_offset, ( phdr->p_offset + phdr->p_filesz ),
	       phdr->p_paddr, ( phdr->p_paddr + phdr->p_filesz ),
	       ( phdr->p_paddr + phdr->p_memsz ) );


	if ( ( rc = prep_segment ( buffer, phdr->p_filesz,
				   phdr->p_memsz ) ) != 0 ) {
		DBGC ( image, "ELF %p could not prepare segment: %s\n",
		       image, strerror ( rc ) );
		return rc;
	}


	memcpy_user ( buffer, 0, image->data, phdr->p_offset, phdr->p_filesz );


	if ( ( e_offset = ( ehdr->e_entry - dest ) ) < phdr->p_filesz ) {
		image->priv.phys = ehdr->e_entry;
		DBGC ( image, "ELF %p found physical entry point at %lx\n",
		       image, image->priv.phys );
	} else if ( ( e_offset = ( ehdr->e_entry - phdr->p_vaddr ) )
		    < phdr->p_filesz ) {
		if ( ! image->priv.phys ) {
			image->priv.phys = ( dest + e_offset );
			DBGC ( image, "ELF %p found virtual entry point at %lx"
			       " (virt %lx)\n", image, image->priv.phys,
			       ( ( unsigned long ) ehdr->e_entry ) );
		}
	}

	return 0;
}
