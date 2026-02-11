knapp5_callback(Widget gw, XtPointer client_data, XtPointer call_data)
{
    switch (global.mode) {
    case NewsModeDisconnected:
	break;
    case NewsModeConnected:
    case NewsModeAllgroups:
    case NewsModeSomegroups:
    case NewsModeNewgroups:
	kill_edit_popup(NULL);
	break;
    case NewsModeGroup:
    case NewsModeThread:
	kill_edit_popup(global.curr_group);
	break;
    }
}
