nfs_direct_good_bytes(struct nfs_direct_req *dreq, struct nfs_pgio_header *hdr)
{
	int i;
	ssize_t count;

	if (dreq->mirror_count == 1) {
		dreq->mirrors[hdr->pgio_mirror_idx].count += hdr->good_bytes;
		dreq->count += hdr->good_bytes;
	} else {

		count = dreq->mirrors[hdr->pgio_mirror_idx].count;
		if (count + dreq->io_start < hdr->io_start + hdr->good_bytes) {
			count = hdr->io_start + hdr->good_bytes - dreq->io_start;
			dreq->mirrors[hdr->pgio_mirror_idx].count = count;
		}


		count = dreq->mirrors[0].count;

		for (i = 1; i < dreq->mirror_count; i++)
			count = min(count, dreq->mirrors[i].count);

		dreq->count = count;
	}
}
