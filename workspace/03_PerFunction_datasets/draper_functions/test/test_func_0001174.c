bc_makeArray(bytecode_input_t *bc, int *pos)
{
    int i;
    const char** array;
    int len = ntohl(bc[*pos].value);

    (*pos)+=2;

    array=(const char **)xmalloc((len+1) * sizeof(char *));

    for (i=0; i<len; i++) {
	*pos = unwrap_string(bc, *pos, &(array[i]), NULL);
    }

    array[i] = NULL;

    return array;
}
