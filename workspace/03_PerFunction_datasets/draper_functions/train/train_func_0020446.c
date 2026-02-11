make_new_buffer(void)
{


    if (openfile == NULL) {
	openfile = make_new_opennode();
	splice_opennode(openfile, openfile, openfile);


    } else {
	splice_opennode(openfile, make_new_opennode(), openfile->next);
	openfile = openfile->next;
    }


    initialize_buffer();
}
