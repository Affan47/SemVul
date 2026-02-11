confirm_callback(Widget    w,
			     XtPointer client_data,
			     XtPointer call_data)
{
    NoticeReply	reply = (NoticeReply)call_data;
    int		catchup = (int)client_data;

    unset_busy();
    XtPopdown(w);
    XtDestroyWidget(w);

    if (reply != NoticeReplyLeft)
	return;

    leave_group(catchup);
}
