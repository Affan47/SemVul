classify (packet, class)
	struct packet *packet;
	struct class *class;
{
	if (packet -> class_count < PACKET_MAX_CLASSES)
		class_reference (&packet -> classes [packet -> class_count++],
				 class, MDL);
	else
		log_error ("too many classes match %s",
		      print_hw_addr (packet -> raw -> htype,
				     packet -> raw -> hlen,
				     packet -> raw -> chaddr));
}
