saa1099_control_port_w( int chip, int reg, int data )
{
	struct SAA1099 *saa = &saa1099[chip];

    if ((data & 0xff) > 0x1c)
	{

                logerror("%04x: (SAA1099 #%d) Unknown register selected\n",activecpu_get_pc(), chip);
	}

    saa->selected_reg = data & 0x1f;
	if (saa->selected_reg == 0x18 || saa->selected_reg == 0x19)
	{

        if (saa->env_clock[0])
			saa1099_envelope(chip,0);
		if (saa->env_clock[1])
			saa1099_envelope(chip,1);
    }
}
