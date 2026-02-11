pdf_run_d(pdf_csi *csi)
{
	pdf_gstate *gstate = csi->gstate + csi->gtop;
	pdf_obj *array;
	int i;
	int len;

	array = csi->obj;
	len = pdf_array_len(array);
	gstate->stroke_state = fz_unshare_stroke_state_with_len(csi->dev->ctx, gstate->stroke_state, len);
	gstate->stroke_state->dash_len = len;
	for (i = 0; i < len; i++)
		gstate->stroke_state->dash_list[i] = pdf_to_real(pdf_array_get(array, i));
	gstate->stroke_state->dash_phase = csi->stack[0];
}
