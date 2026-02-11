lookup_redirection_data (edge e, edge incoming_edge, enum insert_option insert)
{
  void **slot;
  struct redirection_data *elt;


  elt = XNEW (struct redirection_data);
  elt->outgoing_edge = e;
  elt->dup_block = NULL;
  elt->do_not_duplicate = false;
  elt->incoming_edges = NULL;

  slot = htab_find_slot (redirection_data, elt, insert);


  if (slot == NULL)
    {
      free (elt);
      return NULL;
    }


  if (*slot == NULL)
    {
      *slot = (void *)elt;
      elt->incoming_edges = XNEW (struct el);
      elt->incoming_edges->e = incoming_edge;
      elt->incoming_edges->next = NULL;
      return elt;
    }

  else
    {


      free (elt);


      elt = (struct redirection_data *) *slot;


      if (insert)
	{
          struct el *el = XNEW (struct el);
	  el->next = elt->incoming_edges;
	  el->e = incoming_edge;
	  elt->incoming_edges = el;
	}

      return elt;
    }
}
