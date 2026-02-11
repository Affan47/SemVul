gf_odf_write_qos(GF_BitStream *bs, GF_QoS_Descriptor *qos)
{
	GF_Err e;
	u32 size, i;
	GF_QoS_Default *tmp;
	if (!qos) return GF_BAD_PARAM;

	e = gf_odf_size_descriptor((GF_Descriptor *)qos, &size);
	if (e) return e;
	e = gf_odf_write_base_descriptor(bs, qos->tag, size);
	if (e) return e;

	gf_bs_write_int(bs, qos->predefined, 8);

	if (! qos->predefined) {
		i=0;
		while ((tmp = (GF_QoS_Default *)gf_list_enum(qos->QoS_Qualifiers, &i))) {
			e = gf_odf_write_qos_qual(bs, tmp);
			if (e) return e;
		}
	}
	return GF_OK;
}
