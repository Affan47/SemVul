aw_message_timer_listen_event(AW_root *awr, AW_CL cl1, AW_CL cl2)
{
#if defined(TRACE_STATUS_MORE)
    fprintf(stderr, "in aw_message_timer_listen_event\n"); fflush(stdout);
#endif

    AW_window *aww = ((AW_window *)cl1);
    if (aww->is_shown()) {
        aww->activate();
        awr->add_timed_callback_never_disabled(AW_MESSAGE_LISTEN_DELAY, aw_message_timer_listen_event, cl1, cl2);
    }
}
