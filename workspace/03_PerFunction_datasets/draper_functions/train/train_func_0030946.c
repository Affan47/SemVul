gb_font_trim()
{
	int bc,lenptr;
	char *ptr;

	for (bc=0;bc<8;bc++)
	{
		if (gb_font_pointers[bc]==NULL) return;
		ptr=gb_font_pointers[bc];
		while (ptr[0]==' ')
		{
			if (ptr[0]==0) break;
			if (ptr[0]==' ') gb_font_pointers[bc]++;
			ptr++;
		}
		lenptr=strlen(gb_font_pointers[bc])-1;
		ptr=gb_font_pointers[bc];
		while (lenptr>=0)
		{
			if (ptr[lenptr]==' ') { ptr[lenptr]=0; } else { lenptr=0; }
			lenptr--;
		}
	}


}
