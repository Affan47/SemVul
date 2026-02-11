cpu8051_OP_D5(void)
{
unsigned char destaddr = memory_read8( PGM_MEM_ID, cpu8051.pc++ );
unsigned char destination = cpu8051_ReadD( destaddr );
(cpu8051.pc)++;
unsigned int source = ((char) memory_read8(PGM_MEM_ID, cpu8051.pc - 1)) + cpu8051.pc;
destination--;
if ( destination != 0 ) cpu8051.pc = source;
cpu8051_WriteD( destaddr, destination );
return 2;
}
