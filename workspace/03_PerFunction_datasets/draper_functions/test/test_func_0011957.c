cpu8051_OP_94(void)
{
unsigned char destination = cpu8051_ReadD( _ACC_ );
unsigned char source = memory_read8( PGM_MEM_ID, (cpu8051.pc)++ );
unsigned char carryflag = cpu8051_ReadD( _PSW_ ) >> 7;
cpu8051_WriteD( _PSW_, ( cpu8051_ReadD( _PSW_ ) & 0x3B ) );
if ( destination < ( source + carryflag ) ) {
  cpu8051_WriteD( _PSW_, ( cpu8051_ReadD( _PSW_ ) | 0x80 ) );
  if ( ( destination & 0x7F ) > ( ( source + carryflag ) & 0x7F ) )  cpu8051_WriteD( _PSW_, ( cpu8051_ReadD( _PSW_ ) | 0x04 ) );
} else if ( ( destination & 0x7F ) < ( ( source + carryflag ) & 0x7F ) )   cpu8051_WriteD( _PSW_, ( cpu8051_ReadD( _PSW_ ) | 0x04 ) );
if ( ( destination & 0x0F ) < ( ( source + carryflag ) & 0x0F ) )   cpu8051_WriteD( _PSW_, ( cpu8051_ReadD( _PSW_ ) | 0x40 ) );
destination -= source + carryflag;
cpu8051_WriteD( _ACC_, destination );
return 1;
}
