C_translate(void)
{text_pointer p;scrap_pointer save_base=scrap_base;
scrap_base=scrap_ptr;
C_read(true);
if(next_control!='|')err_print("! Missing `|' after C text");

p=translate();
#ifdef STAT
if(scrap_ptr>max_scr_ptr)max_scr_ptr=scrap_ptr;
#endif
scrap_ptr=scrap_base;scrap_base=save_base;return p;
}
