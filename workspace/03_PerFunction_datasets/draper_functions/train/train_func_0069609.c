backsql_cmp_attr( const void *v_m1, const void *v_m2 )
{
	const backsql_at_map_rec	*m1 = v_m1,
					*m2 = v_m2;

	if ( slap_ad_is_binary( m1->bam_ad ) || slap_ad_is_binary( m2->bam_ad ) ) {
#ifdef BACKSQL_USE_PTR_CMP
		return SLAP_PTRCMP( m1->bam_ad->ad_type, m2->bam_ad->ad_type );
#else
		return ber_bvcmp( &m1->bam_ad->ad_type->sat_cname, &m2->bam_ad->ad_type->sat_cname );
#endif
	}

#ifdef BACKSQL_USE_PTR_CMP
	return SLAP_PTRCMP( m1->bam_ad, m2->bam_ad );
#else
	return ber_bvcmp( &m1->bam_ad->ad_cname, &m2->bam_ad->ad_cname );
#endif
}
