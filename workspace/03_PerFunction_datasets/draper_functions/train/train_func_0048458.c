pdf_set_color(pdf_csi *csi, int what, float *v)
{
	fz_context *ctx = csi->dev->ctx;
	pdf_gstate *gs = csi->gstate + csi->gtop;
	pdf_material *mat;
	int i;

	pdf_flush_text(csi);

	mat = what == PDF_FILL ? &gs->fill : &gs->stroke;

	switch (mat->kind)
	{
	case PDF_MAT_PATTERN:
	case PDF_MAT_COLOR:
		if (!strcmp(mat->colorspace->name, "Lab"))
		{
			mat->v[0] = v[0] / 100;
			mat->v[1] = (v[1] + 100) / 200;
			mat->v[2] = (v[2] + 100) / 200;
		}
		for (i = 0; i < mat->colorspace->n; i++)
			mat->v[i] = v[i];
		break;
	default:
		fz_warn(ctx, "color incompatible with material");
	}
}
