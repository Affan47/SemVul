vsp1_pipeline_cleanup(struct vsp1_pipeline *pipe)
{
	mutex_lock(&pipe->lock);


	if (--pipe->use_count == 0)
		__vsp1_pipeline_cleanup(pipe);

	mutex_unlock(&pipe->lock);
}
