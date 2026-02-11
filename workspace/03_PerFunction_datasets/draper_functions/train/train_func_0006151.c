pcfg_print_short(node n)
{
    if (n == 0 || node_get_type(n, LEFT) != PCFG)
	bad_error("error: pcfg_print_short() called on non-PCFG\n");
    n = (node) node_get_ptr(n, RIGHT);
    printf("<");
    while (n != 0) {
	printf("%s ", (char *) node_get_ptr(Car(n), LEFT));
	n = (node) node_get_ptr(n, RIGHT);
    }
    printf(">");
    return n;
}
