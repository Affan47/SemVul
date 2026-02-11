serial_console_setup(char *param)
{
	char *option, *end;
	unsigned long tty;
	unsigned long baud_rate;
	unsigned char parity, bits;

	if (strncmp(param, "ttyS", 4))
		return;

	param += 4;

	tty = simple_strtoul(param, &option, 10);

	if (option == param)
		return;

	if (tty > 3)
		return;

	if (*option == '\0' || *option == ' ')
		goto save_tty;

	if (*option != ',')
		return;


	option++;
	baud_rate = simple_strtoul(option, &end, 10);

	if (end == option)
		return;

	if (baud_rate == 0 || (115200 % baud_rate) != 0)
		return;

	if (*end == '\0' || *end == ' ')
		goto save_baud_rate;

	switch (toupper(*end)) {
		case 'N':
			parity = 0;
			break;
		case 'O':
			parity = UART_LCR_PARITY;
			break;
		case 'E':
			parity = UART_LCR_PARITY | UART_LCR_EPAR;
			break;
		default:

			return;
	}

	end++;
	if (*end == '\0' || *end == ' ')
		goto save_parity;


	if (*end < '7' || *end > '8')
		return;

	bits = *end - '0';

	end++;

	if (*end != '\0' && *end != ' ')
		return;

	serial_bits = bits;
 save_parity:
	serial_parity = parity;
 save_baud_rate:
	serial_baud_rate = (int) baud_rate;
 save_tty:
	serial_tty = (short) tty;
	serial_cons = 1;
}
