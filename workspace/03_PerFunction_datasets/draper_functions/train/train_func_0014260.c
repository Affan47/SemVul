gg_svg_insert_shape (struct gg_svg_document *gg_svg_doc, int type, void *data)
{

    struct gg_svg_group *group;
    struct gg_svg_shape *shape;
    struct gg_svg_clip *clip;
    struct gg_svg_item *item;

    if (gg_svg_doc->current_group == NULL && gg_svg_doc->current_clip == NULL)
      {

	  shape = gg_svg_alloc_shape (type, data, NULL);
	  if (gg_svg_doc->defs_count > 0)
	      shape->is_defs = 1;
	  if (gg_svg_doc->flow_root_count > 0)
	      shape->is_flow_root = 1;
	  item = gg_svg_alloc_item (GG_SVG_ITEM_SHAPE, shape);
	  if (gg_svg_doc->first == NULL)
	      gg_svg_doc->first = item;
	  if (gg_svg_doc->last != NULL)
	      gg_svg_doc->last->next = item;
	  gg_svg_doc->last = item;
      }
    else if (gg_svg_doc->current_group != NULL)
      {

	  group = gg_svg_doc->current_group;
	  shape = gg_svg_alloc_shape (type, data, group);
	  if (gg_svg_doc->defs_count > 0)
	      shape->is_defs = 1;
	  if (gg_svg_doc->flow_root_count > 0)
	      shape->is_flow_root = 1;
	  item = gg_svg_alloc_item (GG_SVG_ITEM_SHAPE, shape);
	  if (group->first == NULL)
	      group->first = item;
	  if (group->last != NULL)
	      group->last->next = item;
	  group->last = item;
      }
    else if (gg_svg_doc->current_clip != NULL)
      {

	  clip = gg_svg_doc->current_clip;
	  shape = gg_svg_alloc_shape (type, data, NULL);
	  if (gg_svg_doc->defs_count > 0)
	      shape->is_defs = 1;
	  if (gg_svg_doc->flow_root_count > 0)
	      shape->is_flow_root = 1;
	  item = gg_svg_alloc_item (GG_SVG_ITEM_SHAPE, shape);
	  if (clip->first == NULL)
	      clip->first = item;
	  if (clip->last != NULL)
	      clip->last->next = item;
	  clip->last = item;
      }
    gg_svg_doc->current_shape = shape;
}
