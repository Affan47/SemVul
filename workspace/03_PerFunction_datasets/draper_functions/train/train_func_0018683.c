ms_objv8_write_link_fmla (BiffPut *bp, guint16 typ,
			  ExcelWriteSheet *esheet,
			  GnmExprTop const *texpr)
{
	char hfmla[10];
	unsigned pos, end_pos;
	guint16 fmla_len;

	pos = bp->curpos;
	GSF_LE_SET_GUINT16 (hfmla, typ);
	GSF_LE_SET_GUINT16 (hfmla + 2, 0);
	GSF_LE_SET_GUINT16 (hfmla + 4, 0);
	GSF_LE_SET_GUINT32 (hfmla + 6, 0);
	ms_biff_put_var_write (bp, hfmla, sizeof hfmla);
	fmla_len = excel_write_formula (esheet->ewb,
					texpr,
					esheet->gnum_sheet, 0, 0,
					EXCEL_CALLED_FROM_OBJ);
	if (fmla_len & 1)
		ms_biff_put_var_write (bp, "", 1);
	end_pos = bp->curpos;
	ms_biff_put_var_seekto (bp, pos);
	GSF_LE_SET_GUINT16 (hfmla + 2, (fmla_len + 7) & ~1);
	GSF_LE_SET_GUINT16 (hfmla + 4, fmla_len);
	ms_biff_put_var_write (bp, hfmla, sizeof hfmla);
	ms_biff_put_var_seekto (bp, end_pos);
}
