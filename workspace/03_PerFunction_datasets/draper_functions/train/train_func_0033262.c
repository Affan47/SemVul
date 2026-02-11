malloc_pat_node()
{
    static int  idx = 1024;
    static char *ptr;

    if (idx == 1024) {
	ptr = malloc(sizeof(pat_node) * idx);
	idx = 0;
    }

    return (pat_node *)(ptr + sizeof(pat_node) * idx++);
}
