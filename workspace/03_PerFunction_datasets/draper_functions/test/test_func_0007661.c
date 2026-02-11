cmd_loop(unsigned numbytes, struct inbuf_t *inbuf)
{
	unsigned char *src = inbuf->data + inbuf->head;
	struct cardstate *cs = inbuf->cs;
	unsigned cbytes = cs->cbytes;
	unsigned procbytes = 0;
	unsigned char c;

	while (procbytes < numbytes) {
		c = *src++;
		procbytes++;

		switch (c) {
		case '\n':
			if (cbytes == 0 && cs->respdata[0] == '\r') {

				cs->respdata[0] = 0;
				break;
			}

		case '\r':

			if (cbytes >= MAX_RESP_SIZE) {
				dev_warn(cs->dev, "response too large (%d)\n",
					 cbytes);
				cbytes = MAX_RESP_SIZE;
			}
			cs->cbytes = cbytes;
			gigaset_dbg_buffer(DEBUG_TRANSCMD, "received response",
					   cbytes, cs->respdata);
			gigaset_handle_modem_response(cs);
			cbytes = 0;


			cs->respdata[0] = c;


			if (cs->dle && !(inbuf->inputstate & INS_DLE_command))
				inbuf->inputstate &= ~INS_command;


			goto exit;

		case DLE_FLAG:
			if (inbuf->inputstate & INS_DLE_char) {

				inbuf->inputstate &= ~INS_DLE_char;
			} else if (cs->dle ||
				   (inbuf->inputstate & INS_DLE_command)) {

				inbuf->inputstate |= INS_DLE_char;
				goto exit;
			}


		default:

			if (cbytes < MAX_RESP_SIZE)
				cs->respdata[cbytes] = c;
			cbytes++;
		}
	}
exit:
	cs->cbytes = cbytes;
	return procbytes;
}
