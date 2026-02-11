fluid_sequencer_add_midi_event_to_buffer(void* data, fluid_midi_event_t* event)
{
	fluid_event_t evt;
	fluid_sequencer_t* seq = (fluid_sequencer_t*) data;
	int chan = fluid_midi_event_get_channel(event);

	fluid_event_clear(&evt);
	fluid_event_set_time(&evt, fluid_sequencer_get_tick(seq));
	fluid_event_set_dest(&evt, get_fluidsynth_dest(seq));

	switch (fluid_midi_event_get_type(event)) {
	case NOTE_OFF:
		fluid_event_noteoff(&evt, chan, fluid_midi_event_get_key(event));
		break;
	case NOTE_ON:
		fluid_event_noteon(&evt, fluid_midi_event_get_channel(event),
		                   fluid_midi_event_get_key(event), fluid_midi_event_get_velocity(event));
		break;
	case CONTROL_CHANGE:
		fluid_event_control_change(&evt, chan, fluid_midi_event_get_control(event),
		                           fluid_midi_event_get_value(event));
		break;
	case PROGRAM_CHANGE:
		fluid_event_program_change(&evt, chan, fluid_midi_event_get_program(event));
		break;
	case PITCH_BEND:
		fluid_event_pitch_bend(&evt, chan, fluid_midi_event_get_pitch(event));
		break;
	case CHANNEL_PRESSURE:
		fluid_event_channel_pressure(&evt, chan, fluid_midi_event_get_program(event));
		break;
	case MIDI_SYSTEM_RESET:
		fluid_event_system_reset(&evt);
		break;
	default:
		return FLUID_FAILED;
	}


	return fluid_sequencer_send_at(seq, &evt, 0, 0);
}
