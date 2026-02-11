BM_ParseCommand(GF_BifsDecoder *codec, GF_BitStream *bs, GF_List *com_list)
{
	u8 go, type;
	u32 count;
	GF_Err e;
	go = 1;
	e = GF_OK;

	codec->LastError = GF_OK;
	count = 0;

	while (go) {
		type = gf_bs_read_int(bs, 2);
		switch (type) {
		case 0:
			e = BM_ParseInsert(codec, bs, com_list);
			break;
		case 1:
			e = BM_ParseDelete(codec, bs, com_list);
			break;
		case 2:
			e = BM_ParseReplace(codec, bs, com_list);
			break;
		case 3:
			e = BM_SceneReplace(codec, bs, com_list);
			break;
		}
		if (e) return e;

		go = gf_bs_read_int(bs, 1);
		count++;

	}
	while (gf_list_count(codec->QPs)) {
		gf_bifs_dec_qp_remove(codec, 1);
	}
	return GF_OK;
}
