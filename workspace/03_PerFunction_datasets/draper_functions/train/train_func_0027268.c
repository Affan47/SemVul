media_entity_pipeline_start(struct media_entity *entity,
					     struct media_pipeline *pipe)
{
	struct media_device *mdev = entity->parent;
	struct media_entity_graph graph;
	struct media_entity *entity_err = entity;
	int ret;

	mutex_lock(&mdev->graph_mutex);

	media_entity_graph_walk_start(&graph, entity);

	while ((entity = media_entity_graph_walk_next(&graph))) {
		DECLARE_BITMAP(active, MEDIA_ENTITY_MAX_PADS);
		DECLARE_BITMAP(has_no_links, MEDIA_ENTITY_MAX_PADS);
		unsigned int i;

		entity->stream_count++;
		WARN_ON(entity->pipe && entity->pipe != pipe);
		entity->pipe = pipe;


		if (entity->stream_count > 1)
			continue;

		if (!entity->ops || !entity->ops->link_validate)
			continue;

		bitmap_zero(active, entity->num_pads);
		bitmap_fill(has_no_links, entity->num_pads);

		for (i = 0; i < entity->num_links; i++) {
			struct media_link *link = &entity->links[i];
			struct media_pad *pad = link->sink->entity == entity
						? link->sink : link->source;


			bitmap_clear(has_no_links, pad->index, 1);


			if (!(pad->flags & MEDIA_PAD_FL_MUST_CONNECT) ||
			    link->flags & MEDIA_LNK_FL_ENABLED)
				bitmap_set(active, pad->index, 1);


			if (link->sink != pad ||
			    !(link->flags & MEDIA_LNK_FL_ENABLED))
				continue;

			ret = entity->ops->link_validate(link);
			if (ret < 0 && ret != -ENOIOCTLCMD) {
				dev_dbg(entity->parent->dev,
					"link validation failed for \"%s\":%u -> \"%s\":%u, error %d\n",
					link->source->entity->name,
					link->source->index,
					entity->name, link->sink->index, ret);
				goto error;
			}
		}


		bitmap_or(active, active, has_no_links, entity->num_pads);

		if (!bitmap_full(active, entity->num_pads)) {
			ret = -EPIPE;
			dev_dbg(entity->parent->dev,
				"\"%s\":%u must be connected by an enabled link\n",
				entity->name,
				(unsigned)find_first_zero_bit(
					active, entity->num_pads));
			goto error;
		}
	}

	mutex_unlock(&mdev->graph_mutex);

	return 0;

error:


	media_entity_graph_walk_start(&graph, entity_err);

	while ((entity_err = media_entity_graph_walk_next(&graph))) {
		entity_err->stream_count--;
		if (entity_err->stream_count == 0)
			entity_err->pipe = NULL;


		if (entity_err == entity)
			break;
	}

	mutex_unlock(&mdev->graph_mutex);

	return ret;
}
