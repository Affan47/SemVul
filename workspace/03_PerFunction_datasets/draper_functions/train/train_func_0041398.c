memStoreByte( machine_6502 *machine, int addr, int value ) {
  machine->memory[ addr ] = (value & 0xff);
  if( (addr >= 0x200) && (addr<=0x5ff) )
    updateDisplayPixel(machine, addr );
}
