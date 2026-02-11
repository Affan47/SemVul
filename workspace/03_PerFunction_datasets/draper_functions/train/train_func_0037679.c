shift_boundaries (filevec)
     struct file_data filevec[];
{
  int f;

  if (inhibit)
    return;

  for (f = 0; f < 2; f++)
    {
      char *changed = filevec[f].changed_flag;
      char const *other_changed = filevec[1-f].changed_flag;
      int const *equivs = filevec[f].equivs;
      int i = 0;
      int j = 0;
      int i_end = filevec[f].buffered_lines;

      while (1)
	{
	  int runlength, start, corresponding;


	  while (i < i_end && changed[i] == 0)
	    {
	      while (other_changed[j++])
		continue;
	      i++;
	    }

	  if (i == i_end)
	    break;

	  start = i;


	  while (changed[++i])
	    continue;
	  while (other_changed[j])
	    j++;

	  do
	    {


	      runlength = i - start;


	      while (start && equivs[start - 1] == equivs[i - 1])
		{
		  changed[--start] = 1;
		  changed[--i] = 0;
		  while (changed[start - 1])
		    start--;
		  while (other_changed[--j])
		    continue;
		}


	      corresponding = other_changed[j - 1] ? i : i_end;


	      while (i != i_end && equivs[start] == equivs[i])
		{
		  changed[start++] = 0;
		  changed[i++] = 1;
		  while (changed[i])
		    i++;
		  while (other_changed[++j])
		    corresponding = i;
		}
	    }
	  while (runlength != i - start);


	  while (corresponding < i)
	    {
	      changed[--start] = 1;
	      changed[--i] = 0;
	      while (other_changed[--j])
		continue;
	    }
	}
    }
}
