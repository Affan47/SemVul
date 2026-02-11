get_vlarb_preempt(struct hfi1_devdata *dd, u32 nelems,
			      struct ib_vl_weight_elem *vl)
{
	unsigned int i;

	for (i = 0; i < nelems; i++, vl++) {
		vl->vl = 0xf;
		vl->weight = 0;
	}
}
