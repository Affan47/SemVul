display_proto(struct rc_device *rc_dev)
{
	if (rc_dev->type == HARDWARE_DECODER)
		fprintf(stderr, "Current protocols: ");
	else
		fprintf(stderr, "Enabled protocols: ");
	show_proto(rc_dev->current);
	fprintf(stderr, "\n");
}
