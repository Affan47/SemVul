mdc_link (call_frame_t *frame, xlator_t *this,
          loc_t *oldloc, loc_t *newloc, dict_t *xdata)
{
        mdc_local_t  *local = NULL;

        local = mdc_local_get (frame);

        loc_copy (&local->loc, oldloc);
        loc_copy (&local->loc2, newloc);

        STACK_WIND (frame, mdc_link_cbk,
                    FIRST_CHILD(this), FIRST_CHILD(this)->fops->link,
                    oldloc, newloc, xdata);
        return 0;
}
