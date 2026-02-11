parport_find_number (int number)
{
	struct parport *port, *result = NULL;

	if (list_empty(&portlist))
		get_lowlevel_driver ();

	spin_lock (&parportlist_lock);
	list_for_each_entry(port, &portlist, list) {
		if (port->number == number) {
			result = parport_get_port (port);
			break;
		}
	}
	spin_unlock (&parportlist_lock);
	return result;
}
