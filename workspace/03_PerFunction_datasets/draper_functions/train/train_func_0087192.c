fput_sem_leaf_subtree(FILE *fp,
                      const SemanticLeaf *leaf,
                      const Module_table *module,
                      char *delim)
{
    int n = 0;
    List *li;

    for (li = leaf->subtree; li != NULL; li = li->next) {
        n += fput_sem_node0(fp, li->data, module);
        if (li->next != NULL){
            n += fprintf(fp, "%s", delim);
	}
    }

    return n;
}
