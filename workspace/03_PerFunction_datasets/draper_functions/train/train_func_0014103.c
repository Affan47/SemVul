add_handlers()
{
    for (int i = 0; i < ninputs(); i++) {
	String s = "tickets" + String(i);
	add_read_handler(s, read_tickets_handler, (void *)i);
	add_write_handler(s, write_tickets_handler, (void *)i);
    }
}
