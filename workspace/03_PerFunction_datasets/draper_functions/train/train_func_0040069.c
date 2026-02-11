vsp1_pipeline_validate(struct vsp1_pipeline *pipe,
				  struct vsp1_video *video)
{
	struct media_entity_graph graph;
	struct media_entity *entity = &video->video.entity;
	struct media_device *mdev = entity->parent;
	unsigned int i;
	int ret;

	mutex_lock(&mdev->graph_mutex);


	media_entity_graph_walk_start(&graph, entity);

	while ((entity = media_entity_graph_walk_next(&graph))) {
		struct v4l2_subdev *subdev;
		struct vsp1_rwpf *rwpf;
		struct vsp1_entity *e;

		if (media_entity_type(entity) != MEDIA_ENT_T_V4L2_SUBDEV) {
			pipe->num_video++;
			continue;
		}

		subdev = media_entity_to_v4l2_subdev(entity);
		e = to_vsp1_entity(subdev);
		list_add_tail(&e->list_pipe, &pipe->entities);

		if (e->type == VSP1_ENTITY_RPF) {
			rwpf = to_rwpf(subdev);
			pipe->inputs[pipe->num_inputs++] = rwpf;
			rwpf->video.pipe_index = pipe->num_inputs;
		} else if (e->type == VSP1_ENTITY_WPF) {
			rwpf = to_rwpf(subdev);
			pipe->output = to_rwpf(subdev);
			rwpf->video.pipe_index = 0;
		} else if (e->type == VSP1_ENTITY_LIF) {
			pipe->lif = e;
		} else if (e->type == VSP1_ENTITY_BRU) {
			pipe->bru = e;
		}
	}

	mutex_unlock(&mdev->graph_mutex);


	if (pipe->num_inputs == 0 || !pipe->output) {
		ret = -EPIPE;
		goto error;
	}


	for (i = 0; i < pipe->num_inputs; ++i) {
		ret = vsp1_pipeline_validate_branch(pipe, pipe->inputs[i],
						    pipe->output);
		if (ret < 0)
			goto error;
	}

	return 0;

error:
	__vsp1_pipeline_cleanup(pipe);
	return ret;
}
