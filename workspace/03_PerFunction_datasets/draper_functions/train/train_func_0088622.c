__setup_next_component (char *path, char *component)
{
        char    *comp = NULL;
        char    *nextcomp = NULL;

        if ((!path) || (!component))
                return NULL;

        strcpy (component, path);
        comp = index (component, (int)'/');
        if (!comp)
                goto err;

        comp++;
        nextcomp = index (comp, (int)'/');
        if (nextcomp) {
                strcpy (path, nextcomp);
                *nextcomp = '\0';
        } else
                path[0] = '\0';

err:
        return comp;
}
