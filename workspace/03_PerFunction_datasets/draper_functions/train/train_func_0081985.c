task_consider( int x, int y )
{
	char command[WAVEFRONT_LINE_MAX];
	char tag[WAVEFRONT_LINE_MAX];

	struct work_queue_task* t;

	if(x>=xsize) return 1;
	if(y>=ysize) return 1;

	if(text_array_get(array,x,y))
	{
		if(bmap)
			bitmap_set(bmap, x, y, WAVEFRONT_TASK_STATE_COMPLETE);
		return 0;
	}

	const char *left   = text_array_get(array,x-1,y);
	const char *bottom = text_array_get(array,x,y-1);
	const char *diag   = text_array_get(array,x-1,y-1);

	if(!left || !bottom || !diag) return 1;

	sprintf(command,"./%s %d %d xfile yfile dfile",function,x,y);
	sprintf(tag,"%d %d",x,y);

	t = work_queue_task_create(command);
	work_queue_task_specify_tag(t,tag);
	work_queue_task_specify_input_file(t, function, function);
	work_queue_task_specify_input_buf(t, left, strlen(left), "xfile");
	work_queue_task_specify_input_buf(t, bottom, strlen(bottom), "yfile");
	work_queue_task_specify_input_buf(t, diag, strlen(diag), "dfile");
	work_queue_submit(queue,t);

	if(bmap)
		bitmap_set(bmap, x, y, WAVEFRONT_TASK_STATE_READY);

	return 1;
}
