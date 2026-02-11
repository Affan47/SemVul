img_ir_control(const struct img_ir_control *control)
{
	u32 ctrl = control->code_type << IMG_IR_CODETYPE_SHIFT;
	if (control->decoden)
		ctrl |= IMG_IR_DECODEN;
	if (control->hdrtog)
		ctrl |= IMG_IR_HDRTOG;
	if (control->ldrdec)
		ctrl |= IMG_IR_LDRDEC;
	if (control->decodinpol)
		ctrl |= IMG_IR_DECODINPOL;
	if (control->bitorien)
		ctrl |= IMG_IR_BITORIEN;
	if (control->d1validsel)
		ctrl |= IMG_IR_D1VALIDSEL;
	if (control->bitinv)
		ctrl |= IMG_IR_BITINV;
	if (control->decodend2)
		ctrl |= IMG_IR_DECODEND2;
	if (control->bitoriend2)
		ctrl |= IMG_IR_BITORIEND2;
	if (control->bitinvd2)
		ctrl |= IMG_IR_BITINVD2;
	return ctrl;
}
