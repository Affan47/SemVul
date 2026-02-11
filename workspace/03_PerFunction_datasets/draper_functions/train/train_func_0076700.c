esas2r_read_vda(struct esas2r_adapter *a, char *buf, long off, int count)
{
	if (!a->vda_buffer)
		return -ENOMEM;

	if (off == 0) {
		struct esas2r_request *rq;
		struct atto_ioctl_vda *vi =
			(struct atto_ioctl_vda *)a->vda_buffer;
		struct esas2r_sg_context sgc;
		bool wait_for_completion;


		rq = esas2r_alloc_request(a);
		if (rq == NULL) {
			esas2r_debug("esas2r_read_vda: out of requestss");
			return -EBUSY;
		}

		rq->comp_cb = vda_complete_req;

		sgc.first_req = rq;
		sgc.adapter = a;
		sgc.cur_offset = a->vda_buffer + VDA_BUFFER_HEADER_SZ;
		sgc.get_phys_addr = (PGETPHYSADDR)get_physaddr_vda;

		a->vda_command_done = 0;

		wait_for_completion =
			esas2r_process_vda_ioctl(a, vi, rq, &sgc);

		if (wait_for_completion) {


			while (!a->vda_command_done)
				wait_event_interruptible(a->vda_waiter,
							 a->vda_command_done);
		}

		esas2r_free_request(a, (struct esas2r_request *)rq);
	}

	if (off > VDA_MAX_BUFFER_SIZE)
		return 0;

	if (count + off > VDA_MAX_BUFFER_SIZE)
		count = VDA_MAX_BUFFER_SIZE - off;

	if (count < 0)
		return 0;

	memcpy(buf, a->vda_buffer + off, count);

	return count;
}
