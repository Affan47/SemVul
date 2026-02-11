frame_in_group (call_frame_t *frame, gid_t gid)
{
        int  i = 0;

        if (frame->root->gid == gid)
                return 1;

        for (i = 0; i < frame->root->ngrps; i++)
                if (frame->root->groups[i] == gid)
                        return 1;
        return 0;
}
