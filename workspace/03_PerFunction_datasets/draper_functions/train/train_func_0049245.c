memorize_variant_topic(THD *thd, TABLE *topics, int count,
			    struct st_find_field *find_fields,
			    List<String> *names,
			    String *name, String *description, String *example)
{
  DBUG_ENTER("memorize_variant_topic");
  MEM_ROOT *mem_root= thd->mem_root;
  if (count==0)
  {
    get_field(mem_root,find_fields[help_topic_name].field,        name);
    get_field(mem_root,find_fields[help_topic_description].field, description);
    get_field(mem_root,find_fields[help_topic_example].field,     example);
  }
  else
  {
    if (count == 1)
      names->push_back(name);
    String *new_name= new (thd->mem_root) String;
    get_field(mem_root,find_fields[help_topic_name].field,new_name);
    names->push_back(new_name);
  }
  DBUG_VOID_RETURN;
}
