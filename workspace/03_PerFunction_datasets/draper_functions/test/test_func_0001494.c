sci_unsolicited_frame_control_get_header(struct sci_unsolicited_frame_control *uf_control,
							 u32 frame_index,
							 void **frame_header)
{
	if (frame_index < SCU_MAX_UNSOLICITED_FRAMES) {


		*frame_header = &uf_control->buffers.array[frame_index].header->data;

		return SCI_SUCCESS;
	}

	return SCI_FAILURE_INVALID_PARAMETER_VALUE;
}
