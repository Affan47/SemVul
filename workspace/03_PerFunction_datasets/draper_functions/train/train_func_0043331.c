m6850_update_io(void)
{
	UINT8 new_state;


	if (!(m6850_sound_status & 0x02))
	{

		if (m6850_status & 0x01)
			m6850_status |= 0x20;


		m6850_input = m6850_sound_output;


		m6850_status |= 0x01;


		m6850_sound_status |= 0x02;
	}


	if (m6850_data_ready)
	{

		if (m6850_sound_status & 0x01)
			m6850_sound_status |= 0x20;


		m6850_sound_input = m6850_output;


		m6850_sound_status |= 0x01;


		m6850_status |= 0x02;
		m6850_data_ready = 0;
	}


	if ((m6850_control & 3) == 3)
	{
		m6850_status = 0x02;
		m6850_data_ready = 0;
	}
	if ((m6850_sound_control & 3) == 3)
		m6850_sound_status = 0x02;


	new_state = 0;
	if ((m6850_control & 0x80) && (m6850_status & 0x21)) new_state = 1;
	if ((m6850_control & 0x60) == 0x20 && (m6850_status & 0x02)) new_state = 1;


	if (new_state && !(m6850_status & 0x80))
	{
		cpu_set_irq_line(0, M6809_FIRQ_LINE, ASSERT_LINE);
		m6850_status |= 0x80;
	}
	else if (!new_state && (m6850_status & 0x80))
	{
		cpu_set_irq_line(0, M6809_FIRQ_LINE, CLEAR_LINE);
		m6850_status &= ~0x80;
	}


	new_state = 0;
	if ((m6850_sound_control & 0x80) && (m6850_sound_status & 0x21)) new_state = 1;
	if ((m6850_sound_control & 0x60) == 0x20 && (m6850_sound_status & 0x02)) new_state = 1;
	if (!(counter_control & 0x20)) new_state = 0;


	if (new_state && !(m6850_sound_status & 0x80))
	{
		cpu_set_nmi_line(1, ASSERT_LINE);
		m6850_sound_status |= 0x80;
	}
	else if (!new_state && (m6850_sound_status & 0x80))
	{
		cpu_set_nmi_line(1, CLEAR_LINE);
		m6850_sound_status &= ~0x80;
	}
}
