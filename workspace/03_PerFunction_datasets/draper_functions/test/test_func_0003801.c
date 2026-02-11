gf_odf_write_segment(GF_BitStream *bs, GF_Segment *sd)
{
	GF_Err e;
	u32 size;
	if (!sd) return GF_BAD_PARAM;
	e = gf_odf_size_descriptor((GF_Descriptor *)sd, &size);
	if (e) return e;
	e = gf_odf_write_base_descriptor(bs, sd->tag, size);
	if (e) return e;
	gf_bs_write_double(bs, sd->startTime);
	gf_bs_write_double(bs, sd->Duration);
	if (sd->SegmentName) {
		gf_bs_write_int(bs, strlen(sd->SegmentName), 8);
		gf_bs_write_data(bs, sd->SegmentName, strlen(sd->SegmentName));
	} else {
		gf_bs_write_int(bs, 0, 8);
	}
	return GF_OK;
}
