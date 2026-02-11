univ8250_request_port(struct uart_port *port)
{
	struct uart_8250_port *up = up_to_u8250p(port);
	int ret;

	ret = base_ops->request_port(port);
	if (ret == 0 && port->type == PORT_RSA) {
		ret = serial8250_request_rsa_resource(up);
		if (ret < 0)
			base_ops->release_port(port);
	}

	return ret;
}
