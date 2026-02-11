pdf_gsave(pdf_csi *csi)
{
	fz_context *ctx = csi->dev->ctx;
	pdf_gstate *gs;

	if (csi->gtop == csi->gcap-1)
	{
		csi->gstate = fz_resize_array(ctx, csi->gstate, csi->gcap*2, sizeof(pdf_gstate));
		csi->gcap *= 2;
	}

	memcpy(&csi->gstate[csi->gtop + 1], &csi->gstate[csi->gtop], sizeof(pdf_gstate));

	csi->gtop++;
	gs = &csi->gstate[csi->gtop];
	pdf_keep_material(ctx, &gs->stroke);
	pdf_keep_material(ctx, &gs->fill);
	if (gs->font)
		pdf_keep_font(ctx, gs->font);
	if (gs->softmask)
		pdf_keep_xobject(ctx, gs->softmask);
	fz_keep_stroke_state(ctx, gs->stroke_state);
}
