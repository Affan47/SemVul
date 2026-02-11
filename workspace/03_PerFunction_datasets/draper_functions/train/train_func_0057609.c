save_value(struct control * cp, int port, float value) {
	switch (port) {
	case IR_PORT_PREDELAY: cp->predelay = value;
		break;
	case IR_PORT_ATTACK: cp->attack = value;
		break;
	case IR_PORT_ATTACKTIME: cp->attacktime = value;
		break;
	case IR_PORT_ENVELOPE: cp->envelope = value;
		break;
	case IR_PORT_LENGTH: cp->length = value;
		break;
	case IR_PORT_STRETCH: cp->stretch = value;
		break;
	case IR_PORT_STEREO_IR: cp->stereo_ir = value;
		break;
	}
}
