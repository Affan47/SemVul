check_ScopedPdu(tvbuff_t* tvb)
{
	int offset;
	gint8 ber_class;
	gboolean pc;
	gint32 tag;
	int hoffset, eoffset;
	guint32 len;

	offset = get_ber_identifier(tvb, 0, &ber_class, &pc, &tag);
	offset = get_ber_length(tvb, offset, NULL, NULL);

	if ( ! (((ber_class!=BER_CLASS_APP) && (ber_class!=BER_CLASS_PRI) )
			&& ( (!pc) || (ber_class!=BER_CLASS_UNI) || (tag!=BER_UNI_TAG_ENUMERATED) )
			)) return FALSE;

	if((tvb_get_guint8(tvb, offset)==0)&&(tvb_get_guint8(tvb, offset+1)==0))
		return TRUE;

	hoffset = offset;

	offset = get_ber_identifier(tvb, offset, &ber_class, &pc, &tag);
	offset = get_ber_length(tvb, offset, &len, NULL);
	eoffset = offset + len;

	if (eoffset <= hoffset) return FALSE;

	if ((ber_class!=BER_CLASS_APP)&&(ber_class!=BER_CLASS_PRI))
		if( (ber_class!=BER_CLASS_UNI)
			||((tag<BER_UNI_TAG_NumericString)&&(tag!=BER_UNI_TAG_OCTETSTRING)&&(tag!=BER_UNI_TAG_UTF8String)) )
			return FALSE;

	return TRUE;

}
