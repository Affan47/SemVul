cpu8051_OP_B5(void)
{
unsigned char destination = cpu8051_ReadD( _ACC_ );
unsigned char srcaddr = memory_read8( PGM_MEM_ID, (cpu8051.pc)++ );
unsigned char source = cpu8051_ReadD( srcaddr );
unsigned int reladdr = ((char) memory_read8(PGM_MEM_ID, cpu8051.pc)) + (cpu8051.pc + 1);
cpu8051_WriteD( _PSW_, ( cpu8051_ReadD( _PSW_ ) & 0x7F ) );
if ( destination < source ) cpu8051_WriteD( _PSW_, ( cpu8051_ReadD( _PSW_ ) | 0x80 ) );
if ( destination != source ) cpu8051.pc = reladdr;
cpu8051_WriteD( _ACC_, destination );
return 2;
}
