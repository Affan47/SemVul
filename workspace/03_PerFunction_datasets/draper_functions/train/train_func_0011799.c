netsnmp_sysORTable_foreach(void (*f)(const struct sysORTable*, void*), void* c)
{
    DEBUGMSGTL(("agent/sysORTable", "foreach(%p, %p)\n", f, c));
    if(table) {
        data_node run = table;
        do {
            data_node tmp = run;
            run = run->next;
            f(&tmp->data, c);
        } while(table && run != table);
    }
}
