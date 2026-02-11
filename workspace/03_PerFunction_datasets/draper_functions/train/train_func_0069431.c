avc_identify_subunit(struct firedtv *fdtv)
{
	struct avc_command_frame *c = (void *)fdtv->avc_data;
	struct avc_response_frame *r = (void *)fdtv->avc_data;
	int ret;

	mutex_lock(&fdtv->avc_mutex);

	c->ctype   = AVC_CTYPE_CONTROL;
	c->subunit = AVC_SUBUNIT_TYPE_TUNER | fdtv->subunit;
	c->opcode  = AVC_OPCODE_READ_DESCRIPTOR;

	c->operand[0] = DESCRIPTOR_SUBUNIT_IDENTIFIER;
	c->operand[1] = 0xff;
	c->operand[2] = 0x00;
	c->operand[3] = 0x00;
	c->operand[4] = 0x08;
	c->operand[5] = 0x00;
	c->operand[6] = 0x0d;
	clear_operands(c, 7, 8);

	fdtv->avc_data_length = 12;
	ret = avc_write(fdtv);
	if (ret < 0)
		goto out;

	if ((r->response != AVC_RESPONSE_STABLE &&
	     r->response != AVC_RESPONSE_ACCEPTED) ||
	    (r->operand[3] << 8) + r->operand[4] != 8) {
		dev_err(fdtv->device, "cannot read subunit identifier\n");
		ret = -EINVAL;
	}
out:
	mutex_unlock(&fdtv->avc_mutex);

	return ret;
}
