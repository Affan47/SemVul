fluid_midi_dump_postrouter(void* data, fluid_midi_event_t* event)
{
	switch (event->type) {
	case NOTE_ON:
		fprintf(stdout, "event_post_noteon %i %i %i\n",
		        event->channel, event->param1, event->param2);
		break;
	case NOTE_OFF:
		fprintf(stdout, "event_post_noteoff %i %i %i\n",
		        event->channel, event->param1, event->param2);
		break;
	case CONTROL_CHANGE:
		fprintf(stdout, "event_post_cc %i %i %i\n",
		        event->channel, event->param1, event->param2);
		break;
	case PROGRAM_CHANGE:
		fprintf(stdout, "event_post_prog %i %i\n", event->channel, event->param1);
		break;
	case PITCH_BEND:
		fprintf(stdout, "event_post_pitch %i %i\n", event->channel, event->param1);
		break;
	case CHANNEL_PRESSURE:
		fprintf(stdout, "event_post_cpress %i %i\n", event->channel, event->param1);
		break;
	case KEY_PRESSURE:
		fprintf(stdout, "event_post_kpress %i %i %i\n",
		        event->channel, event->param1, event->param2);
		break;
	default:
		break;
	}
	return fluid_synth_handle_midi_event((fluid_synth_t*) data, event);
}
