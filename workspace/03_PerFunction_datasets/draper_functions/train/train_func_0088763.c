file_reader_add_file(struct file_rd_info *fri, char *name)
{


  struct file_list *np, *new;

  new = (struct file_list *) xmalloc (sizeof (struct file_list));
  new->name = name;
  new->next = NULL;

  for (np = fri->the_files; (np != NULL) && (np->next != NULL); np = np->next)
    ;

  if (np == NULL)
    {

      fri->the_files = new;
    }
  else
    {


      np->next = new;
    }
}
