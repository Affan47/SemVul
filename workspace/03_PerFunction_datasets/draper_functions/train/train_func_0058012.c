interact_parse(machine *m)
{
    FILE *file = stdin;
    printf("-> ");
    closure *rep = parse_file(file);
    while (rep != NULL){
	m = eval(rep, m);
	if (m->accum != NULL){
	    print_closure(m->accum);
	}
	printf("\n");
	printf("-> ");
	rep = parse_file(file);
    }
}
