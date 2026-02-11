giraffe_frameset_set_groups(cpl_frameset* set, GiGroupInfo *groups)
{

    cpl_frame* frame = NULL;


    if (set == NULL) {
        return -1;
    }

    if (groups == NULL || groups->tag == NULL) {
        return 0;
    }

    frame = cpl_frameset_get_first(set);

    while (frame != NULL) {

        const cxchar* tag = cpl_frame_get_tag(frame);

        if (tag != NULL &&
            cpl_frame_get_group(frame) == CPL_FRAME_GROUP_NONE) {

            const GiGroupInfo* g = groups;

            while (g->tag != NULL) {
                if (strcmp(tag, g->tag) == 0) {
                    cpl_frame_set_group(frame, g->group);
                    break;
                }
                ++g;
            }

        }

        frame = cpl_frameset_get_next(set);

    }

    return 0;

}
