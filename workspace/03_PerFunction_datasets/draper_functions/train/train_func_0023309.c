sis_int_malloc(struct sis_video_info *ivideo, struct sis_memreq *req)
{
	struct SIS_OH *poh = NULL;

	if((ivideo) && (ivideo->sisfb_id == SISFB_ID) && (!ivideo->havenoheap))
		poh = sisfb_poh_allocate(&ivideo->sisfb_heap, (u32)req->size);

	if(poh == NULL) {
		req->offset = req->size = 0;
		DPRINTK("sisfb: Video RAM allocation failed\n");
	} else {
		req->offset = poh->offset;
		req->size = poh->size;
		DPRINTK("sisfb: Video RAM allocation succeeded: 0x%lx\n",
			(poh->offset + ivideo->video_vbase));
	}
}
