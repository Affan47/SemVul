ivtv_yuv_setup_stream_frame(struct ivtv *itv)
{
	struct yuv_playback_info *yi = &itv->yuv_info;
	struct ivtv_dma_frame dma_args;

	ivtv_yuv_next_free(itv);


	dma_args.y_source = NULL;
	dma_args.uv_source = NULL;
	dma_args.src.left = 0;
	dma_args.src.top = 0;
	dma_args.src.width = yi->v4l2_src_w;
	dma_args.src.height = yi->v4l2_src_h;
	dma_args.dst = yi->main_rect;
	dma_args.src_width = yi->v4l2_src_w;
	dma_args.src_height = yi->v4l2_src_h;


	ivtv_yuv_setup_frame(itv, &dma_args);

	if (!itv->dma_data_req_offset)
		itv->dma_data_req_offset = yuv_offset[yi->draw_frame];
}
