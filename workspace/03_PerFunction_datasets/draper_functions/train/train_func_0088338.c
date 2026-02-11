regex_probe(const char *p, int len, struct proto *proto)
{
    regex_t** probe_list = (regex_t**)(proto->data);
    int i=0;

    while (probe_list[i]) {
        if (!regexec(probe_list[i], p, 0, NULL, 0)) {
            return 1;
        }
        i++;
    }
    return 0;
}
