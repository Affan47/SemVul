ps2mult_interrupt(struct serio *serio,
				     unsigned char data, unsigned int dfl)
{
	struct ps2mult *psm = serio_get_drvdata(serio);
	struct ps2mult_port *in_port;
	unsigned long flags;

	dev_dbg(&serio->dev, "Received %02x flags %02x\n", data, dfl);

	spin_lock_irqsave(&psm->lock, flags);

	if (psm->escape) {
		psm->escape = false;
		in_port = psm->in_port;
		if (in_port->registered)
			serio_interrupt(in_port->serio, data, dfl);
		goto out;
	}

	switch (data) {
	case PS2MULT_ESCAPE:
		dev_dbg(&serio->dev, "ESCAPE\n");
		psm->escape = true;
		break;

	case PS2MULT_BSYNC:
		dev_dbg(&serio->dev, "BSYNC\n");
		psm->in_port = psm->out_port;
		break;

	case PS2MULT_SESSION_START:
		dev_dbg(&serio->dev, "SS\n");
		break;

	case PS2MULT_SESSION_END:
		dev_dbg(&serio->dev, "SE\n");
		break;

	case PS2MULT_KB_SELECTOR:
		dev_dbg(&serio->dev, "KB\n");
		psm->in_port = &psm->ports[PS2MULT_KBD_PORT];
		break;

	case PS2MULT_MS_SELECTOR:
		dev_dbg(&serio->dev, "MS\n");
		psm->in_port = &psm->ports[PS2MULT_MOUSE_PORT];
		break;

	default:
		in_port = psm->in_port;
		if (in_port->registered)
			serio_interrupt(in_port->serio, data, dfl);
		break;
	}

 out:
	spin_unlock_irqrestore(&psm->lock, flags);
	return IRQ_HANDLED;
}
