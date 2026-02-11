interactive_mode(void)
{
    char line[1024];
    void *tree;
    RESULT result = { 0, 0, 0, NULL };

    printf("\neval> ");
    for (fgets(line, sizeof(line), stdin); !feof(stdin); fgets(line, sizeof(line), stdin)) {
	if (line[strlen(line) - 1] == '\n')
	    line[strlen(line) - 1] = '\0';
	if (strlen(line) > 0) {
	    if (Compile(line, &tree) != -1) {
		Eval(tree, &result);
		if (result.type == R_NUMBER) {
		    printf("%g\n", R2N(&result));
		} else if (result.type == R_STRING) {
		    printf("'%s'\n", R2S(&result));
		} else if (result.type == (R_NUMBER | R_STRING)) {
		    printf("'%s' (%g)\n", R2S(&result), R2N(&result));
		} else {
		    printf("internal error: unknown result type %d\n", result.type);
		}
		DelResult(&result);
	    }
	    DelTree(tree);
	}
	printf("eval> ");
    }
    printf("\n");
}
