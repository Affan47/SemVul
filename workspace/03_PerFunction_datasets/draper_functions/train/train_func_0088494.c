cx_edit_fullpath(void)
{
	edit_macro(strcmp(USTR(ppanel_file->dir),"/") ? " $1/$F " : " /$F ");
}
