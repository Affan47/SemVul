se_find_value_in_list(struct snmp_enum_list *list, const char *label)
{
    if (!list)
        return SE_DNE;
    while (list) {
        if (strcmp(list->label, label) == 0)
            return (list->value);
        list = list->next;
    }

    return SE_DNE;
}
