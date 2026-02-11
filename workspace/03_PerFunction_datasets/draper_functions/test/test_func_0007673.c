nvkm_mm_free(struct nvkm_mm *mm, struct nvkm_mm_node **pthis)
{
	struct nvkm_mm_node *this = *pthis;

	if (this) {
		struct nvkm_mm_node *prev = node(this, prev);
		struct nvkm_mm_node *next = node(this, next);

		if (prev && prev->type == NVKM_MM_TYPE_NONE) {
			prev->length += this->length;
			list_del(&this->nl_entry);
			kfree(this); this = prev;
		}

		if (next && next->type == NVKM_MM_TYPE_NONE) {
			next->offset  = this->offset;
			next->length += this->length;
			if (this->type == NVKM_MM_TYPE_NONE)
				list_del(&this->fl_entry);
			list_del(&this->nl_entry);
			kfree(this); this = NULL;
		}

		if (this && this->type != NVKM_MM_TYPE_NONE) {
			list_for_each_entry(prev, &mm->free, fl_entry) {
				if (this->offset < prev->offset)
					break;
			}

			list_add_tail(&this->fl_entry, &prev->fl_entry);
			this->type = NVKM_MM_TYPE_NONE;
		}
	}

	*pthis = NULL;
}
