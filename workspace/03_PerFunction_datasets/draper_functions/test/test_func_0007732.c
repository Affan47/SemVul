connect_input_signals ()

{
	port.input()->channel_pressure[channel_number].connect
		(mem_fun (*this, &Channel::process_chanpress));
	port.input()->channel_note_on[channel_number].connect
		(mem_fun (*this, &Channel::process_note_on));
	port.input()->channel_note_off[channel_number].connect
		(mem_fun (*this, &Channel::process_note_off));
	port.input()->channel_poly_pressure[channel_number].connect
		(mem_fun (*this, &Channel::process_polypress));
	port.input()->channel_program_change[channel_number].connect
		(mem_fun (*this, &Channel::process_program_change));
	port.input()->channel_controller[channel_number].connect
		(mem_fun (*this, &Channel::process_controller));
	port.input()->channel_pitchbend[channel_number].connect
		(mem_fun (*this, &Channel::process_pitchbend));
	port.input()->reset.connect (mem_fun (*this, &Channel::process_reset));
}
