BLOCK_Head( void )
#else
BLOCK_Head( )
#endif
{
	gen("{\n");
	tabs++;
	if ( !GenCC ) gen1("zzBLOCK(zztasp%d);\n", BlkLevel);
}
