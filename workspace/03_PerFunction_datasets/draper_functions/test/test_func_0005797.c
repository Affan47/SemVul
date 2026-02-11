emit_pci_rom_hdr(void)
{
    rom_header_t *pci_hdr;
    pci_hdr_ob_off = opc;
    pci_hdr = (rom_header_t *)(ostart + pci_hdr_ob_off);

    EMIT_STRUCT(rom_header_t);


    LITTLE_ENDIAN_WORD_STORE(pci_hdr->signature,0xaa55);


    LITTLE_ENDIAN_WORD_STORE( pci_hdr->reserved ,
	(sizeof(rom_header_t) + sizeof(pci_data_t)) ) ;


    LITTLE_ENDIAN_WORD_STORE(pci_hdr->data_ptr, sizeof(rom_header_t) );

}
