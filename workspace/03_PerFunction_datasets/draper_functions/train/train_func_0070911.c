write_coff_eeprom( struct prog_info *pi, int address, unsigned char data){

    if ( !GET_ARG(pi->args, ARG_COFF) )
        return;


    if ( ci->pEEPRomMemory ) {
        if ( address <= pi->device->eeprom_size ) {
            *(ci->pEEPRomMemory + address) = data;
            if ( address >= ci->MaxEepromAddress )
                ci->MaxEepromAddress = address;
        } else {
            pi->error_count++;
            fprintf(stderr, "Error: EEPROM address %d exceeds max range %d", address, pi->device->eeprom_size );
        }
    }
}
