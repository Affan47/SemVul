FreeTabular(TabularT *table)
{
    int i;
    for (i=0; i <= table->n; i++) {
        if(table->after[i] ) free(table->after[i]);
        if(table->before[i]) free(table->before[i]);
    }
    free(table->align);
    free(table->vert);
    free(table->chars);
    free(table->width);
    free(table->cline);
    free(table->after);
    free(table->before);
    free(table);
    table = NULL;
}
