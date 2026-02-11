gf_sc_user_event(GF_Compositor *compositor, GF_Event *event)
{
	switch (event->type) {
	case GF_EVENT_SHOWHIDE:
	case GF_EVENT_MOVE:
	case GF_EVENT_SET_CAPTION:
		compositor->video_out->ProcessEvent(compositor->video_out, event);
		return 0;
	default:
		return gf_sc_on_event_ex(compositor, event, 1);
	}
}
