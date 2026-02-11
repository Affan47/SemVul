gg_svg_insert_group (struct gg_svg_document *gg_svg_doc)
{

    struct gg_svg_item *item;
    struct gg_svg_group *parent;
    struct gg_svg_group *group = gg_svg_alloc_group ();
    if (gg_svg_doc->current_group != NULL)
      {

	  parent = gg_svg_doc->current_group;
	  group->parent = parent;
	  if (gg_svg_doc->defs_count > 0)
	      group->is_defs = 1;
	  if (gg_svg_doc->flow_root_count > 0)
	      group->is_flow_root = 1;
	  item = gg_svg_alloc_item (GG_SVG_ITEM_GROUP, group);
	  if (parent->first == NULL)
	      parent->first = item;
	  if (parent->last != NULL)
	      parent->last->next = item;
	  parent->last = item;
	  gg_svg_doc->current_group = group;
	  return;
      }
    if (gg_svg_doc->current_clip != NULL)
      {

	  if (gg_svg_doc->defs_count > 0)
	      group->is_defs = 1;
	  if (gg_svg_doc->flow_root_count > 0)
	      group->is_flow_root = 1;
	  item = gg_svg_alloc_item (GG_SVG_ITEM_GROUP, group);
	  if (gg_svg_doc->current_clip->first == NULL)
	      gg_svg_doc->current_clip->first = item;
	  if (gg_svg_doc->current_clip->last != NULL)
	      gg_svg_doc->current_clip->last->next = item;
	  gg_svg_doc->current_clip->last = item;
	  gg_svg_doc->current_group = group;
	  return;
      }

    parent = gg_svg_doc->current_group;
    group->parent = parent;
    if (gg_svg_doc->defs_count > 0)
	group->is_defs = 1;
    if (gg_svg_doc->flow_root_count > 0)
	group->is_flow_root = 1;
    item = gg_svg_alloc_item (GG_SVG_ITEM_GROUP, group);
    if (gg_svg_doc->first == NULL)
	gg_svg_doc->first = item;
    if (gg_svg_doc->last != NULL)
	gg_svg_doc->last->next = item;
    gg_svg_doc->last = item;
    gg_svg_doc->current_group = group;
}
