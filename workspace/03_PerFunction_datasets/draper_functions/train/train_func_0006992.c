tb_port_add_nfc_credits(struct tb_port *port, int credits)
{
	if (credits == 0)
		return 0;
	tb_port_info(port,
		     "adding %#x NFC credits (%#x -> %#x)",
		     credits,
		     port->config.nfc_credits,
		     port->config.nfc_credits + credits);
	port->config.nfc_credits += credits;
	return tb_port_write(port, &port->config.nfc_credits,
			     TB_CFG_PORT, 4, 1);
}
