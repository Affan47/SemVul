TriggerNotifyMessageProc (XIMS ims,
                                      IMProtocol *call_data,
                                      unsigned char *p)
{
    Xi18n i18n_core = ims->protocol;
    FrameMgr fm;
    extern XimFrameRec trigger_notify_fr[], trigger_notify_reply_fr[];
    register int total_size;
    unsigned char *reply = NULL;
    IMTriggerNotifyStruct *trigger =
        (IMTriggerNotifyStruct *) &call_data->triggernotify;
    CARD16 connect_id = call_data->any.connect_id;
    CARD16 input_method_ID;
    CARD32 flag;

    fm = FrameMgrInit (trigger_notify_fr,
                       (char *) p,
                       _Xi18nNeedSwap (i18n_core, connect_id));

    FrameMgrGetToken (fm, input_method_ID);
    FrameMgrGetToken (fm, trigger->icid);
    FrameMgrGetToken (fm, trigger->flag);
    FrameMgrGetToken (fm, trigger->key_index);
    FrameMgrGetToken (fm, trigger->event_mask);


    flag = trigger->flag;

    FrameMgrFree (fm);

    fm = FrameMgrInit (trigger_notify_reply_fr,
                       NULL,
                       _Xi18nNeedSwap (i18n_core, connect_id));

    total_size = FrameMgrGetTotalSize (fm);
    reply = (unsigned char *) malloc (total_size);
    if (!reply)
    {
        _Xi18nSendMessage (ims, connect_id, XIM_ERROR, 0, 0, 0);
        return;
    }

    memset (reply, 0, total_size);
    FrameMgrSetBuffer (fm, reply);

    FrameMgrPutToken (fm, input_method_ID);
    FrameMgrPutToken (fm, trigger->icid);


    if (flag == 0)
    {

        _Xi18nSendMessage (ims,
                           connect_id,
                           XIM_TRIGGER_NOTIFY_REPLY,
                           0,
                           reply,
                           total_size);
        IMPreeditStart (ims, (XPointer)call_data);
    }

    if (i18n_core->address.improto)
    {
        if (!(i18n_core->address.improto(ims, call_data)))
            return;

    }


    if (flag == 1)
    {

        IMPreeditEnd (ims, (XPointer) call_data);
        _Xi18nSendMessage (ims,
                           connect_id,
                           XIM_TRIGGER_NOTIFY_REPLY,
                           0,
                           reply,
                           total_size);
    }

    FrameMgrFree (fm);
    XFree (reply);
}
