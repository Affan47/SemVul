generate_boundary(const char * boundary_prefix)
{
    char id[MAX_MESSAGE_ID];
    time_t now;
    char name[MAX_MESSAGE_ID];
    long value;

    now = time(NULL);
    value = random();

    gethostname(name, MAX_MESSAGE_ID);

    if (boundary_prefix == NULL)
        boundary_prefix = "";

    snprintf(id, MAX_MESSAGE_ID, "%s%lx_%lx_%x", boundary_prefix, now, value, getpid());

    return strdup(id);
}
