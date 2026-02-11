hide_etherboot ( void ) {
	struct memory_map memmap;
	unsigned int rm_ds_top;
	unsigned int rm_cs_top;
	unsigned int fbms;


	DBG ( "Hiding gPXE from system memory map\n" );
	get_memmap ( &memmap );


	if ( FAKE_E820 ) {
		DBG ( "Hooking in fake E820 map\n" );
		fake_e820();
		get_memmap ( &memmap );
	}


	hide_basemem();
	hide_umalloc ( virt_to_phys ( _textdata ), virt_to_phys ( _textdata ) );
	hide_textdata();


	rm_cs_top = ( ( ( rm_cs << 4 ) + _text16_memsz + 1024 - 1 ) >> 10 );
	rm_ds_top = ( ( ( rm_ds << 4 ) + _data16_memsz + 1024 - 1 ) >> 10 );
	fbms = get_fbms();
	if ( ( rm_cs_top < fbms ) && ( rm_ds_top < fbms ) ) {
		DBG ( "Detected potentially unsafe UNDI load at CS=%04x "
		      "DS=%04x FBMS=%dkB\n", rm_cs, rm_ds, fbms );
		DBG ( "Disabling INT 15 memory hiding\n" );
		return;
	}


	hook_bios_interrupt ( 0x15, ( unsigned int ) int15,
			      &int15_vector );


	DBG ( "Hidden gPXE from system memory map\n" );
	get_memmap ( &memmap );
}
