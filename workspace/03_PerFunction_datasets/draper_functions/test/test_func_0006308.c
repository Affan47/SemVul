gn_atem_incoming_data_handle(char *buffer, int length)
{
	int count;
	unsigned char out_buf[3];

	for (count = 0; count < length ; count++) {


		if (buffer[count] == ModemRegisters[REG_CR] ||
		    buffer[count] == ModemRegisters[REG_LF] ||
		    buffer[count] == ModemRegisters[REG_CTRLZ] ||
		    buffer[count] == ModemRegisters[REG_ESCAPE]) {


			if (buffer[count] == ModemRegisters[REG_CR] &&
				(ModemRegisters[REG_ECHO] & BIT_ECHO)) {
				gn_atem_string_out("\r\n");
			}


			if (buffer[count] == ModemRegisters[REG_CTRLZ] ||
			    buffer[count] == ModemRegisters[REG_ESCAPE])
				CmdBuffer[CurrentCmdBuffer][CurrentCmdBufferIndex++] = buffer[count];

			CmdBuffer[CurrentCmdBuffer][CurrentCmdBufferIndex] = 0x00;

			Parser(CmdBuffer[CurrentCmdBuffer]);

			CurrentCmdBuffer++;
			if (CurrentCmdBuffer >= MAX_CMD_BUFFERS) {
				CurrentCmdBuffer = 0;
			}
			CurrentCmdBufferIndex = 0;

		} else if (buffer[count] == ModemRegisters[REG_BS]) {
			if (CurrentCmdBufferIndex > 0) {

				if (ModemRegisters[REG_ECHO] & BIT_ECHO) {
					gn_atem_string_out("\b \b");
				}

				CurrentCmdBufferIndex--;
			}
		} else {

			if (ModemRegisters[REG_ECHO] & BIT_ECHO) {
				out_buf[0] = buffer[count];
				out_buf[1] = 0;
				gn_atem_string_out((char *)out_buf);
			}


			CmdBuffer[CurrentCmdBuffer][CurrentCmdBufferIndex++] = buffer[count];
			if (CurrentCmdBufferIndex >= CMD_BUFFER_LENGTH) {
				CurrentCmdBufferIndex = CMD_BUFFER_LENGTH;
			}
		}
	}
}
