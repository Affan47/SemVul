update_sge(struct hfi1_sge_state *ss, u32 length)
{
	struct hfi1_sge *sge = &ss->sge;

	sge->vaddr += length;
	sge->length -= length;
	sge->sge_length -= length;
	if (sge->sge_length == 0) {
		if (--ss->num_sge)
			*sge = *ss->sg_list++;
	} else if (sge->length == 0 && sge->mr->lkey) {
		if (++sge->n >= HFI1_SEGSZ) {
			if (++sge->m >= sge->mr->mapsz)
				return;
			sge->n = 0;
		}
		sge->vaddr = sge->mr->map[sge->m]->segs[sge->n].vaddr;
		sge->length = sge->mr->map[sge->m]->segs[sge->n].length;
	}
}
