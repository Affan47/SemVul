dwc2_recalc_initial_desc_idx(struct dwc2_hsotg *hsotg,
					struct dwc2_qh *qh)
{
	u16 frame, fr_idx, fr_idx_tmp, skip_frames;


	if (qh->channel) {
		frame = dwc2_calc_starting_frame(hsotg, qh, &skip_frames);


		fr_idx_tmp = dwc2_frame_list_idx(frame);
		fr_idx = (FRLISTEN_64_SIZE +
			  dwc2_frame_list_idx(qh->sched_frame) - fr_idx_tmp)
			 % dwc2_frame_incr_val(qh);
		fr_idx = (fr_idx + fr_idx_tmp) % FRLISTEN_64_SIZE;
	} else {
		qh->sched_frame = dwc2_calc_starting_frame(hsotg, qh,
							   &skip_frames);
		fr_idx = dwc2_frame_list_idx(qh->sched_frame);
	}

	qh->td_first = qh->td_last = dwc2_frame_to_desc_idx(qh, fr_idx);

	return skip_frames;
}
