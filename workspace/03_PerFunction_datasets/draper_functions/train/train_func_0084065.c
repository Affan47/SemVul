profile_clear_relation(profile_t profile, const char **names)
{
    errcode_t       retval;
    struct profile_node *section, *node;
    void            *state;
    const char      **cpp;

    if (profile->vt) {
        if (!profile->vt->update_relation)
            return PROF_UNSUPPORTED;
        return profile->vt->update_relation(profile->cbdata, names, NULL,
                                            NULL);
    }

    retval = rw_setup(profile);
    if (retval)
        return retval;

    if (names == 0 || names[0] == 0 || names[1] == 0)
        return PROF_BAD_NAMESET;

    section = profile->first_file->data->root;
    for (cpp = names; cpp[1]; cpp++) {
        state = 0;
        retval = profile_find_node(section, *cpp, 0, 1,
                                   &state, &section);
        if (retval)
            return retval;
    }

    state = 0;
    do {
        retval = profile_find_node(section, *cpp, 0, 0, &state, &node);
        if (retval)
            return retval;
        retval = profile_remove_node(node);
        if (retval)
            return retval;
    } while (state);

    profile->first_file->data->flags |= PROFILE_FILE_DIRTY;

    return 0;
}
