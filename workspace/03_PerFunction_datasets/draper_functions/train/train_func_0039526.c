dw_mci_push_part_bytes(struct dw_mci *host, void *buf, int cnt)
{
	cnt = min(cnt, (1 << host->data_shift) - host->part_buf_count);
	memcpy((void *)&host->part_buf + host->part_buf_count, buf, cnt);
	host->part_buf_count += cnt;
	return cnt;
}
