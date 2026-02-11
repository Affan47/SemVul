delayed_command_w(int data)
{
	sound_command = data & 0xff;
	pending_command = 1;


	if (data & 0x100)
		cpu_set_nmi_line(1, ASSERT_LINE);
}
