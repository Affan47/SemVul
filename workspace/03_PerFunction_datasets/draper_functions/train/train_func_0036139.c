gGraphCreateColorMapRelative (const void *color_rule, double min, double max,
			      unsigned char background_red,
			      unsigned char background_green,
			      unsigned char background_blue,
			      const void **color_map)
{

    double last_value = DBL_MAX;
    unsigned char last_red;
    unsigned char last_green;
    unsigned char last_blue;
    double percent;
    gGraphColorMapPtr map;
    gGraphColorRuleItemPtr item;
    gGraphColorRulePtr rule = (gGraphColorRulePtr) color_rule;

    if (rule == NULL)
	return GGRAPH_INVALID_COLOR_RULE;
    if (rule->signature != GG_COLOR_RULE_MAGIC_SIGNATURE)
	return GGRAPH_INVALID_COLOR_RULE;
    if (rule->needs_range == 0)
	return GGRAPH_INVALID_COLOR_RULE;

    *color_map = NULL;
    map = gg_color_map_create ();
    if (!map)
	return GGRAPH_INSUFFICIENT_MEMORY;
    map->no_data_red = background_red;
    map->no_data_green = background_green;
    map->no_data_blue = background_blue;
    map->not_found_red = background_red;
    map->not_found_green = background_green;
    map->not_found_blue = background_blue;

    percent = (max - min) / 100.0;
    item = rule->first;
    while (item)
      {

	  if (item->is_percent)
	      item->value = min + (percent * item->percent_value);
	  item = item->next;
      }

    item = rule->first;
    while (item)
      {

	  if (last_value != DBL_MAX && last_value != item->value)
	    {
		if (resolve_interval
		    (map, last_value, item->value, last_red, last_green,
		     last_blue, item->red, item->green,
		     item->blue) != GGRAPH_OK)
		    goto error;
	    }
	  last_value = item->value;
	  last_red = item->red;
	  last_green = item->green;
	  last_blue = item->blue;
	  item = item->next;
      }
    color_map_prepare (map);
    if (map->array == NULL)
	goto error;
    *color_map = map;
    return GGRAPH_OK;

  error:
    gg_color_map_destroy (map);
    return GGRAPH_ERROR;
}
