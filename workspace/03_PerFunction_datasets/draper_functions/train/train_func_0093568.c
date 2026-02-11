vsp1_entity_destroy(struct vsp1_entity *entity)
{
	if (entity->video)
		vsp1_video_cleanup(entity->video);
	if (entity->subdev.ctrl_handler)
		v4l2_ctrl_handler_free(entity->subdev.ctrl_handler);
	media_entity_cleanup(&entity->subdev.entity);
}
