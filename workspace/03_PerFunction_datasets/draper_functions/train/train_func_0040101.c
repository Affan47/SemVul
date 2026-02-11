clear_sec_mod(void)
{
    struct snmp_secmod_list *tmp = registered_services, *next = NULL;

    while (tmp != NULL) {
	next = tmp->next;
	SNMP_FREE(tmp->secDef);
	SNMP_FREE(tmp);
	tmp = next;
    }
    registered_services = NULL;
}
