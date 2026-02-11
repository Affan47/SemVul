F_close(void)
{
    char c;

    G_debug(2, "F_close()");

    if (first)
	return;

    fprintf(parent_send, "D");
    fflush(parent_send);
    c = fgetc(parent_recv);
    G_debug(2, "PARENT: received %c\n", c);

    first = 1;
}
