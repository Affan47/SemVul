netsnmp_free_all_list_data(netsnmp_data_list *head)
{
    netsnmp_data_list *tmpptr;
    for (; head;) {
        netsnmp_free_list_data(head);
        tmpptr = head;
        head = head->next;
        SNMP_FREE(tmpptr);
    }
}
