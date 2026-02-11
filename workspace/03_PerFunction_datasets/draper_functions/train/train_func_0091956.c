makeBddAbl (ptr_circuit, expr, ptr_befig, vhb_count, createAux, ppAux)
     pCircuit ptr_circuit;
     chain_list *expr;
     struct befig *ptr_befig;
     int *vhb_count;
     int createAux;
     chain_list **ppAux;
{
  short oper;
  pNode pt;
  chain_list *lstGbd;
  chain_list *ptr_cntrl = ptr_ctrlst;
  struct beaux *ptr_beaux = ptr_befig->BEAUX;
  int index;
  char *atom;

  if (expr == NULL)
    {
      printf ("makeBddAbl : Error - ABL = NULL \n");
      exit (1);
    }

  if (ATOM (expr))
    {
      atom = (char *) VALUE_ATOM (expr);

      if (!strcmp (atom, "'0'"))
	return (zero);
      if (!strcmp (atom, "'1'"))
	return (one);
      if (!strcmp (atom, "'d'"))
	return (zero);

      if ((index = searchInputCct (ptr_circuit, atom)) != VIDETH)
	{
	  return (createNodeTermBdd (index));
	}

      else

	{

	  while ((ptr_beaux != NULL) && (strcmp (ptr_beaux->NAME, atom)))
	    ptr_beaux = ptr_beaux->NEXT;

	  if (ptr_beaux == NULL)
	    {
	      printf ("makeBddAbl : Error - signal '%s' not found\n", atom);
	      exit (1);
	    }
	  else

	    {


	      while ((ptr_cntrl != NULL) && ((char *) ptr_cntrl->DATA != atom))
		ptr_cntrl = ptr_cntrl->NEXT;

	      if (ptr_cntrl != NULL)


		{
		  printf ("makeBddAbl : Error - signal '%s' belongs to a combinatory loop \n", atom);
		  exit (1);
		}
	      else
		{
		  if (ptr_beaux->NODE == NULL)
		    {
		      ptr_ctrlst = addchain (ptr_ctrlst, (void *) atom);


		      ptr_beaux->NODE = makeBddAbl (ptr_circuit, ptr_beaux->ABL, ptr_befig,
					       vhb_count, createAux, ppAux);

		      *vhb_count = *vhb_count + 1;
		      ptr_ctrlst = delchain (ptr_ctrlst, ptr_ctrlst);


		      if (numberNodeBdd (ptr_beaux->NODE) > createAux)
			{
			  *ppAux = addchain (*ppAux, ptr_beaux->NAME);
			  return (createNodeTermBdd
			      (addInputCct (ptr_circuit, ptr_beaux->NAME)));
			}

		      return (ptr_beaux->NODE);
		    }
		  else
		    {
		      return (ptr_beaux->NODE);
		    }
		}
	    }
	}
    }
  else
    {
      oper = OPER (expr);
      lstGbd = NULL;
      while ((expr = CDR (expr)))
	{
	  pNode ptNode = makeBddAbl (ptr_circuit, CAR (expr), ptr_befig,
				     vhb_count, createAux, ppAux);
	  lstGbd = addListBdd (lstGbd, ptNode);
	}


      if (oper == STABLE)
	oper = NOT;
      pt = applyBdd (oper, lstGbd);
      freechain (lstGbd);
      return (pt);
    }
}
