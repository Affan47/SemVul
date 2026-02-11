print_folders(FPROC_S *fp)
{
    if(open_printer(_("folder list")) == 0){
	(void) folder_list_text(ps_global, fp, print_char, NULL, 80);

	close_printer();
    }
}
