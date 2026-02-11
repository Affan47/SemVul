esa_read_all(t_TEXT *Text) {

	Text->ESA = (t_ESA*) malloc (sizeof(t_ESA) * Text->length);
	if (!Text->ESA) perror ("esa_read_all");

return 0;
}
