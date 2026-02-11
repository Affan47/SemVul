full_header_callback(Widget w,
				 XtPointer client_data,
				 XtPointer call_data)
{
    if (global.busy || (global.mode != NewsModeGroup &&
			global.mode != NewsModeThread))
	return;

    if (global.curr_art)
	read_article(global.curr_art, True, NULL, NULL);
    else
	set_message("No selected article!", True);
}
