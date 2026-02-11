exprToCLBeh (beh)
     befig_list *beh;
{
  beout_list *out;
  beaux_list *aux;
  bebus_list *bus;
  bebux_list *bux;
  bereg_list *reg;
  bemsg_list *msg;
  biabl_list *biabl;
  chain_list *ret = NULL;

  out = beh->BEOUT;
  while (out)
    {
      ret = addchain (ret, out->ABL);
      out = out->NEXT;
    }

  aux = beh->BEAUX;
  while (aux)
    {
      ret = addchain (ret, aux->ABL);
      aux = aux->NEXT;
    }

  bus = beh->BEBUS;
  while (bus)
    {
      biabl = bus->BIABL;
      while (biabl)
	{
	  ret = addchain (ret, biabl->VALABL);
	  ret = addchain (ret, biabl->CNDABL);
	  biabl = biabl->NEXT;
	}
      bus = bus->NEXT;
    }

  bux = beh->BEBUX;
  while (bux)
    {
      biabl = bux->BIABL;
      while (biabl)
	{
	  ret = addchain (ret, biabl->VALABL);
	  ret = addchain (ret, biabl->CNDABL);
	  biabl = biabl->NEXT;
	}
      bux = bux->NEXT;
    }


  reg = beh->BEREG;
  while (reg)
    {
      biabl = reg->BIABL;
      while (biabl)
	{
	  ret = addchain (ret, biabl->VALABL);
	  ret = addchain (ret, biabl->CNDABL);
	  biabl = biabl->NEXT;
	}
      reg = reg->NEXT;
    }
  msg = beh->BEMSG;
  while (msg)
    {
      ret = addchain (ret, msg->ABL);
      msg = msg->NEXT;
    }
  return ret;
}
