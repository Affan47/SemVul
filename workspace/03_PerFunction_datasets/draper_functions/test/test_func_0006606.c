UPD7759_port_w(int chip, UINT8 data)
{
	struct UPD7759_chip *ch = &UPD7759_chips.chip[chip];

	if(Machine->sample_rate == 0)
		return;

	if(chip >= UPD7759_chips.intf->num) {
		logerror("UPD7759_port_w() called with channel = %d, but only %d channels allocated\n", chip, UPD7759_chips.intf->num);
		return;
	}

	ch->port = data;

	if(UPD7759_chips.intf->mode == UPD7759_SLAVE_MODE) {
		timer_adjust(ch->timer, TIME_IN_HZ(DRQ_FREQUENCY), chip, TIME_IN_HZ(DRQ_FREQUENCY));
		UPD7759_cmd_w(chip, data);
	}
}
