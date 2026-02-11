excel_write_BOF (BiffPut *bp, MsBiffFileType type)
{
	guint8 *data;
	unsigned ans;
	guint    len = 8;
	guint16  record;

	switch (bp->version) {
	case MS_BIFF_V2: record = BIFF_BOF_v0; break;
	case MS_BIFF_V3: record = BIFF_BOF_v2; break;
	case MS_BIFF_V4: record = BIFF_BOF_v4; break;

	case MS_BIFF_V8: len = 16;
	case MS_BIFF_V7: record = BIFF_BOF_v8; break;
	default:
		g_warning ("Unknown biff version '%d' requested.", bp->version);
		return 0;
	}
	data = ms_biff_put_len_next (bp, record, len);
	ans = bp->streamPos;

	switch (type) {
	case MS_BIFF_TYPE_Workbook:
		GSF_LE_SET_GUINT16 (data+2, 0x0005);
		break;
	case MS_BIFF_TYPE_VBModule:
		GSF_LE_SET_GUINT16 (data+2, 0x0006);
		break;
	case MS_BIFF_TYPE_Worksheet:
		GSF_LE_SET_GUINT16 (data+2, 0x0010);
		break;
	case MS_BIFF_TYPE_Chart:
		GSF_LE_SET_GUINT16 (data+2, 0x0020);
		break;
	case MS_BIFF_TYPE_Macrosheet:
		GSF_LE_SET_GUINT16 (data+2, 0x0040);
		break;
	case MS_BIFF_TYPE_Workspace:
		GSF_LE_SET_GUINT16 (data+2, 0x0100);
		break;
	default:
		g_warning ("Unknown type.");
		break;
	}

	switch (bp->version) {
	case MS_BIFF_V8:
		GSF_LE_SET_GUINT16 (data+ 0, 0x0600);
		GSF_LE_SET_GUINT16 (data+ 4, 0x2775);
		GSF_LE_SET_GUINT16 (data+ 6, 0x07cd);
		GSF_LE_SET_GUINT32 (data+ 8, 0x000080c9);
		GSF_LE_SET_GUINT32 (data+12, 0x00000206);
		break;

	case MS_BIFF_V7:
		GSF_LE_SET_GUINT16 (data, 0x0500);


	case MS_BIFF_V5:
		GSF_LE_SET_GUINT16 (data+4, 0x096c);
		GSF_LE_SET_GUINT16 (data+6, 0x07c9);
		break;

	default:
		g_printerr ("FIXME: I need some magic numbers\n");
		GSF_LE_SET_GUINT16 (data+4, 0x0);
		GSF_LE_SET_GUINT16 (data+6, 0x0);
		break;
	}
	ms_biff_put_commit (bp);

	return ans;
}
