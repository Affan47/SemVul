_Xi18nSetEventMask (XIMS ims,
                         CARD16 connect_id,
                         CARD16 im_id,
                         CARD16 ic_id,
                         CARD32 forward_mask,
                         CARD32 sync_mask)
{
    Xi18n i18n_core = ims->protocol;
    FrameMgr fm;
    extern XimFrameRec set_event_mask_fr[];
    unsigned char *reply = NULL;
    register int total_size;

    fm = FrameMgrInit (set_event_mask_fr,
                       NULL,
                       _Xi18nNeedSwap (i18n_core, connect_id));

    total_size = FrameMgrGetTotalSize (fm);
    reply = (unsigned char *) malloc (total_size);
    if (!reply)
        return;

    memset (reply, 0, total_size);
    FrameMgrSetBuffer (fm, reply);

    FrameMgrPutToken (fm, im_id);
    FrameMgrPutToken (fm, ic_id);
    FrameMgrPutToken (fm, forward_mask);
    FrameMgrPutToken (fm, sync_mask);

    _Xi18nSendMessage (ims,
                       connect_id,
                       XIM_SET_EVENT_MASK,
                       0,
                       reply,
                       total_size);

    FrameMgrFree (fm);
    XFree(reply);
}
