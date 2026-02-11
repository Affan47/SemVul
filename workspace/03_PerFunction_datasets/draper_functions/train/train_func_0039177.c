emimsg_destroy(struct emimsg *emimsg)
{
    int len;

    len = emimsg->num_fields;
    while (--len >= 0) {
        octstr_destroy(emimsg->fields[len]);
        emimsg->fields[len] = NULL;
    }
    gw_free(emimsg->fields);
    gw_free(emimsg);
}
