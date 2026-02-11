load_cache_table (char *file_name)
{
  cache_entry *cache = NULL;
  cache_entry **last = &cache;
  table *file = table_open (file_name);
  table_entry *entry;
  while ((entry = table_read (file)) != NULL)
    {
      cache_entry *new_rule = ZALLOC (cache_entry);
      new_rule->line = entry->line;
      new_rule->entry_type = name2i (entry->field[ca_type], cache_type_map);
      new_rule->name = entry->field[ca_derived_name];
      filter_parse (&new_rule->original_fields, entry->field[ca_field_name]);
      new_rule->type = entry->field[ca_type_def];

      if (entry->nr_fields > ca_expression)
	{
	  int len = 0;
	  int chi;
	  for (chi = ca_expression; chi < entry->nr_fields; chi++)
	    {
	      len += strlen (" : ") + strlen (entry->field[chi]);
	    }
	  new_rule->expression = NZALLOC (char, len);
	  strcpy (new_rule->expression, entry->field[ca_expression]);
	  for (chi = ca_expression + 1; chi < entry->nr_fields; chi++)
	    {
	      strcat (new_rule->expression, " : ");
	      strcat (new_rule->expression, entry->field[chi]);
	    }
	}

      *last = new_rule;
      last = &new_rule->next;
    }
  return cache;
}
