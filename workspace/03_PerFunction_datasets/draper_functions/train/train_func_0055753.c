parse_animation_block(char *buffer, size_t buffer_size, FILE *fichier, CFanimation *parent) {
    CFmovement *first = NULL;
    CFmovement *current = NULL;
    CFmovement *next;
    char *time;
    char *name;
    char *parameters;
    int tick;
    CFanimationHook *animationhook;

    if (parent->verbose)
        cf_log(llevDebug, "CFAnim: In parse block for %s\n", buffer);
    while (fgets(buffer, buffer_size, fichier)) {
        if (buffer[0] == '[')
            break;
        if (buffer[0] == '#')
            continue;
        buffer[strlen(buffer)-strlen("\n")] = '\0';
        while (buffer[strlen(buffer)-1] == ' ')
            buffer[strlen(buffer)-1] = '\0';
        if (strlen(buffer) <= 0)
            continue;
        time = buffer;

        name = strstr(buffer, " ");
        if (!name)
            continue;
        *name = '\0';
        name++;
        while (*name == ' ')
            name++;

        tick = atoi(time);
        if (tick < 0)
            continue;

        parameters = strstr(name, " ");
        if (parameters) {
            *parameters = '\0';
            parameters++;
            while (*parameters == ' ')
                parameters++;
            if (*parameters == '\0')
                parameters = NULL;
        }
        animationhook = get_command(name);
        if (parent->verbose) {
            if (!animationhook)
                cf_log(llevError, "CFAnim: %s - Unknown animation command\n", name);
            else
                cf_log(llevDebug, "CFAnim: Parsed %s -> %p\n", name, animationhook);
        }
        if (!animationhook) {
            if (parent->errors_allowed)
                continue;
            else
                break;
        }
        next = (CFmovement *)malloc(sizeof(CFmovement));
        if (!next)
            continue;
        next->parent = parent;
        next->tick = tick;
        next->next = NULL;
        if (animationhook->funcinit)
            next->id = animationhook->funcinit(name, parameters, next);
        next->func = animationhook->funcrun;
        if (current)
            current->next = next;
        else
            first = next;
        current = next;
    }
    return first;
}
