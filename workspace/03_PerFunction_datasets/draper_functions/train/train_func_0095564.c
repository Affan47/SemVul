fuse_resolve_and_resume (fuse_state_t *state, fuse_resume_fn_t fn)
{
        xlator_t *inode_xl = NULL;
        xlator_t *active_xl = NULL;

        fuse_gfid_set (state);

        state->resume_fn = fn;

        active_xl = fuse_active_subvol (state->this);
        inode_xl = fuse_state_subvol (state);
        if (!inode_xl && state->loc.parent)
                inode_xl = state->loc.parent->table->xl;


        if (inode_xl == active_xl) {

                if (!(state->loc2.parent || state->loc2.inode))
                        goto resume;

                inode_xl = NULL;


                if (state->loc2.inode)
                        inode_xl = state->loc2.inode->table->xl;
                if (!inode_xl && state->loc2.parent)
                        inode_xl = state->loc2.parent->table->xl;

                if (inode_xl == active_xl)
                        goto resume;
        }


        if (state->fd)
                goto resume;


        state->itable = active_xl->itable;

        fuse_resolve_all (state);

        return 0;
resume:
        fn (state);

        return 0;
}
