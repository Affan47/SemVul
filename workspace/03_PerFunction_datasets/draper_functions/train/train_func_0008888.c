forward_from_resolved_tree(struct link_node *curr_node,
						    struct link_node **target,
						    int *nres,
						    int *nopen)
{

  struct link_node *lnp;

  lnp = curr_node;

  if (lnp->first_child)
    {


      if (lnp->first_child != *target)
	{
	  printf("ERROR: forward failed, has first_child that's NOT tar\n");
	  exit(ABEND_EXIT);
	}
      else
	{


	  if ((lnp->first_child)->next_sibling ||
	      (lnp->first_child)->first_child)
	    {
	      printf("ERROR: forward failed with target child (has sibs)\n");
	      exit(ABEND_EXIT);
	    }
	  else
	    {


	      *target = NULL;
	      if ((lnp->current_clause)->type == BOTH)
		{


		  lnp = lnp->first_child;
		  *nopen = *nopen + 1;
		}
	      else
		{

		  free_linked_node_tree(lnp->first_child, target);
		  lnp->first_child = NULL;
		  *nres = *nres - 1;
		  *nopen = *nopen + 1;
		  lnp->current_clause = NULL;
		}
	    }
	}
    }
  else
    {

      *nres = *nres - 1;
      *nopen = *nopen + 1;
      lnp->current_clause = NULL;
    }

  return lnp;

}
