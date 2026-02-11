get_sguid(struct hfi1_ibport *ibp, unsigned index)
{
	if (!index) {
		struct hfi1_pportdata *ppd = ppd_from_ibp(ibp);

		return cpu_to_be64(ppd->guid);
	}
	return ibp->guids[index - 1];
}
