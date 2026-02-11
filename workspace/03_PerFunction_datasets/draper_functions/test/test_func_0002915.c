gdi_ui_memblt(struct rdp_inst * inst, uint8 opcode, int x, int y, int cx, int cy, FRDP_HBITMAP src, int srcx, int srcy)
{
	GDI_IMAGE *gdi_bmp;
	GDI *gdi = GET_GDI(inst);

	DEBUG_GDI("gdi_ui_memblt: x:%d y:%d cx:%d cy:%d srcx:%d, srcy:%d rop:0x%X",
	          x, y, cx, cy, srcx, srcy, gdi_rop3_code(opcode));

	gdi_bmp = (GDI_IMAGE*) src;
	gdi_BitBlt(gdi->drawing->hdc, x, y, cx, cy, gdi_bmp->hdc, srcx, srcy, gdi_rop3_code(opcode));
}
