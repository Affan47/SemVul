bfb_stuff_data(uint8_t *buffer, uint8_t type, uint8_t *data, uint16_t len, uint8_t seq)
{
        int i;
        union {
                uint16_t value;
                uint8_t bytes[2];
        } fcs;


	if (type == 1) {
		buffer[0] = 0x01;
		buffer[1] = ~buffer[0];
		return 2;
	}


	if (type != 2 && type != 3) {
		buffer[0] = 0x00;
		return 0;
	}

	buffer[0] = type;
	buffer[1] = ~buffer[0];
	buffer[2] = seq;

	fcs.value = htons(len);
	buffer[3] = fcs.bytes[0];
	buffer[4] = fcs.bytes[1];


	memcpy(&buffer[5], data, len);


        fcs.value = INIT_FCS;

        for (i=2; i < len+5; i++) {
                fcs.value = irda_fcs(fcs.value, buffer[i]);
        }

        fcs.value = ~fcs.value;


	buffer[len+5] = fcs.bytes[0];
	buffer[len+6] = fcs.bytes[1];

	return len+7;
}
