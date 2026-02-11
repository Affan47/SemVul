trak_AddBox(GF_Box *s, GF_Box *a)
{
	GF_TrackBox *ptr = (GF_TrackBox *)s;
	if (!a) return GF_OK;
	switch(a->type) {
	case GF_ISOM_BOX_TYPE_TKHD:
		if (ptr->Header) return GF_ISOM_INVALID_FILE;
		ptr->Header = (GF_TrackHeaderBox *)a;
		return GF_OK;
	case GF_ISOM_BOX_TYPE_EDTS:
		if (ptr->editBox) return GF_ISOM_INVALID_FILE;
		ptr->editBox = (GF_EditBox *)a;
		return GF_OK;
	case GF_ISOM_BOX_TYPE_UDTA:
		if (ptr->udta) return GF_ISOM_INVALID_FILE;
		ptr->udta = (GF_UserDataBox *)a;
		return GF_OK;
	case GF_ISOM_BOX_TYPE_META:
		if (ptr->meta) return GF_ISOM_INVALID_FILE;
		ptr->meta = (GF_MetaBox *)a;
		return GF_OK;
	case GF_ISOM_BOX_TYPE_TREF:
		if (ptr->References) return GF_ISOM_INVALID_FILE;
		ptr->References = (GF_TrackReferenceBox *)a;
		return GF_OK;
	case GF_ISOM_BOX_TYPE_MDIA:
		if (ptr->Media) return GF_ISOM_INVALID_FILE;
		ptr->Media = (GF_MediaBox *)a;
		((GF_MediaBox *)a)->mediaTrack = ptr;
		return GF_OK;
	default:
		return gf_isom_box_add_default(s, a);
	}
	return GF_OK;
}
