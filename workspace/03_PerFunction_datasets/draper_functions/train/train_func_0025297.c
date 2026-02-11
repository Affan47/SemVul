selected_folders(CONTEXT_S *context)
{
    int	      i, n, total;

    n = folder_total(FOLDERS(context));
    for(total = i = 0; i < n; i++)
      if(folder_entry(i, FOLDERS(context))->selected)
	total++;

    return(total);
}
