cpia2_allocate_buffers(struct camera_data *cam)
{
	int i;

	if(!cam->buffers) {
		u32 size = cam->num_frames*sizeof(struct framebuf);
		cam->buffers = kmalloc(size, GFP_KERNEL);
		if(!cam->buffers) {
			ERR("couldn't kmalloc frame buffer structures\n");
			return -ENOMEM;
		}
	}

	if(!cam->frame_buffer) {
		cam->frame_buffer = rvmalloc(cam->frame_size*cam->num_frames);
		if (!cam->frame_buffer) {
			ERR("couldn't vmalloc frame buffer data area\n");
			kfree(cam->buffers);
			cam->buffers = NULL;
			return -ENOMEM;
		}
	}

	for(i=0; i<cam->num_frames-1; ++i) {
		cam->buffers[i].next = &cam->buffers[i+1];
		cam->buffers[i].data = cam->frame_buffer +i*cam->frame_size;
		cam->buffers[i].status = FRAME_EMPTY;
		cam->buffers[i].length = 0;
		cam->buffers[i].max_length = 0;
		cam->buffers[i].num = i;
	}
	cam->buffers[i].next = cam->buffers;
	cam->buffers[i].data = cam->frame_buffer +i*cam->frame_size;
	cam->buffers[i].status = FRAME_EMPTY;
	cam->buffers[i].length = 0;
	cam->buffers[i].max_length = 0;
	cam->buffers[i].num = i;
	cam->curbuff = cam->buffers;
	cam->workbuff = cam->curbuff->next;
	DBG("buffers=%p, curbuff=%p, workbuff=%p\n", cam->buffers, cam->curbuff,
	    cam->workbuff);
	return 0;
}
