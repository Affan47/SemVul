focaltech_process_touch_packet(struct psmouse *psmouse,
					   unsigned char *packet)
{
	struct focaltech_data *priv = psmouse->private;
	struct focaltech_hw_state *state = &priv->state;
	unsigned char fingers = packet[1];
	int i;

	state->pressed = (packet[0] >> 4) & 1;


	for (i = 0; i < FOC_MAX_FINGERS; i++) {
		state->fingers[i].active = fingers & 0x1;
		if (!state->fingers[i].active) {


			state->fingers[i].valid = false;
		}
		fingers >>= 1;
	}
}
