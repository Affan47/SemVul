edd_has_mbr_signature(struct edd_device *edev)
{
	return edev->index < min_t(unsigned char, edd.mbr_signature_nr, EDD_MBR_SIG_MAX);
}
