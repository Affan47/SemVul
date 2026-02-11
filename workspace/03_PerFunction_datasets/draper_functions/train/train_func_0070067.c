get_value(char *name) {
        FORMAT_NODE *node;

#ifdef DEBUG
        ASSERT(name);
#endif

        if (strlen(name) == 0)
                return EMPTY_FIELD;

        if ((node = get_field(name))) {
                return node->value;
        } else {
                return EMPTY_FIELD;
        }
}
