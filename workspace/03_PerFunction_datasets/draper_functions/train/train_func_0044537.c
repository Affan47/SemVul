join_same_trees(HUFF_COUNTS *huff_counts, uint trees)
{
  uint k,tree_number;
  HUFF_COUNTS count,*i,*j,*last_count;

  last_count=huff_counts+trees;
  for (tree_number=0, i=huff_counts ; i < last_count ; i++)
  {
    if (!i->tree->tree_number)
    {
      i->tree->tree_number= ++tree_number;
      if (i->tree_buff)
	continue;
      for (j=i+1 ; j < last_count ; j++)
      {
	if (! j->tree->tree_number && ! j->tree_buff)
	{
	  for (k=0 ; k < 256 ; k++)
	    count.counts[k]=i->counts[k]+j->counts[k];
	  if (calc_packed_length(&count,1) <=
	      i->tree->bytes_packed + j->tree->bytes_packed+
	      i->tree->tree_pack_length+j->tree->tree_pack_length+
	      ALLOWED_JOIN_DIFF)
	  {
	    memcpy(i->counts, count.counts,
			 sizeof(count.counts[0])*256);
	    my_free(j->tree->element_buffer);
	    j->tree->element_buffer=0;
	    j->tree=i->tree;
	    bmove((uchar*) i->counts,(uchar*) count.counts,
		  sizeof(count.counts[0])*256);
	    if (make_huff_tree(i->tree,i))
	      return (uint) -1;
	  }
	}
      }
    }
  }
  DBUG_PRINT("info", ("Original trees:  %d  After join: %d",
                      trees, tree_number));
  if (verbose)
    printf("Original trees:  %d  After join: %d\n", trees, tree_number);
  return tree_number;
}
