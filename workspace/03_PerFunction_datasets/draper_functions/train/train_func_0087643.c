register_delayed_action(XmtMsgLineWidget mw, int when, int action)
#else
static void register_delayed_action(mw, when, action)
XmtMsgLineWidget mw;
int when;
int action;
#endif
{


    if (mw->msgline.delayed_action && (mw->msgline.delayed_action != action))
	handle_delayed_action(mw);


    if (mw->msgline.delayed_action == action) {
	if (when == XmtMsgLineNow) {
	    handle_delayed_action(mw);
	    return;
	}
	else if ((mw->msgline.action_hook_id && (when == XmtMsgLineOnAction))||
		 (mw->msgline.timer_id && (when > 0)))
	    return;
    }
    else if (when != XmtMsgLineNow)
	mw->msgline.delayed_action = action;

    switch(when) {
    case XmtMsgLineNow:
	if (action == CLEAR)
	    _XmtMsgLineClear(mw);
	else if (action == POP)
	    _XmtMsgLinePop(mw);
	break;
    case XmtMsgLineOnAction:


	if (mw->msgline.hook_being_deleted)
	    mw->msgline.hook_being_deleted = False;
	else
	    mw->msgline.action_hook_id =
		XtAppAddActionHook(XtWidgetToApplicationContext((Widget)mw),
				   action_hook, (XtPointer)mw);
	break;
    default:
	mw->msgline.timer_id =
	    XtAppAddTimeOut(XtWidgetToApplicationContext((Widget)mw),
			    when, timer_proc, (XtPointer)mw);
	break;
    }
}
