ad_marker_info_received(struct bond_marker *marker_info,
	struct port *port)
{
	struct bond_marker marker;


	memcpy(&marker, marker_info, sizeof(struct bond_marker));

	marker.tlv_type = AD_MARKER_RESPONSE_SUBTYPE;


	if (ad_marker_send(port, &marker) >= 0) {
		pr_debug("Sent Marker Response on port %d\n",
			 port->actor_port_number);
	}
}
