list(const char* typ, const char* var, void* val, int siz)
#else
list(typ, var, val, siz)
char* typ;
char* var;
void* val;
int siz;
#endif
{
	register unsigned char*	u = (unsigned char*)val;
	register unsigned char*	e = u + siz;

	printf("#define _ast_%s_%s_init\t0x%02x", typ, var, *u);
	while (++u < e)
		printf(",0x%02x", *u);
	printf("\n");
}
