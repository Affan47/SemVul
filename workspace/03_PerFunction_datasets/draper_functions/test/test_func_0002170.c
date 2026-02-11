obp_qual_set(struct ofw_dev *ofwdev, const char *qual)
{
	if (!strcmp("bootp", qual))
		ofwdev->quals[ofwdev->qual_count++] = OBP_QUAL_BOOTP;
	else if (!strcmp("dhcpv6", qual))
		ofwdev->quals[ofwdev->qual_count++] = OBP_QUAL_DHCPV6;
	else if (!strcmp("ipv6", qual))
		ofwdev->quals[ofwdev->qual_count++] = OBP_QUAL_IPV6;
	else if (!strcmp("iscsi", qual)) {
		ofwdev->type = OFW_DT_ISCSI;
		ofwdev->quals[ofwdev->qual_count++] = OBP_QUAL_ISCSI;
	} else if (!strcmp("ping", qual))
		ofwdev->quals[ofwdev->qual_count++] = OBP_QUAL_PING;
	else
		printf("%s: %s UNKNOWN\n", __func__, qual);
	return qual;
}
