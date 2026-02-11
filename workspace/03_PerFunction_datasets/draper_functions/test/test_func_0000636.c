print_gen_entry_path (line_ref *line, gen_entry *table, error_func *print)
{
  if (table->parent == NULL)
    {
      if (table->top->model != NULL)
	print (line, "%s", table->top->model->name);
      else
	print (line, "");
    }
  else
    {
      print_gen_entry_path (line, table->parent, print);
      print (NULL, ".%d", table->opcode_nr);
    }
}
