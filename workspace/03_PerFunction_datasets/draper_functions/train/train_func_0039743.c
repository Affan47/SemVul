par_resize(root)
	TREE *root;
{
  TREE *newroot;

  while(symbol == resize)
  {
    newroot = newtree();
    VDATA(newroot) = opr_resize;
    ETYPE(newroot) = ETYPE_OPER;
    scan(); LEFT(newroot) = nameorvar();
    RIGHT(newroot) = root;
    root = newroot;

    switch(symbol)
    {
      case reduction:
        LEFT(newroot) = par_reduction(LEFT(newroot));
      break;

      case and: case or:
        LEFT(newroot) = par_logical(LEFT(newroot));
      break;

      case vector:
        LEFT(newroot) = par_vector(LEFT(newroot));
      break;

      case eq: case neq: case lt: case gt: case le: case ge:
        LEFT(newroot) = par_compare(LEFT(newroot));
      break;

      case plus: case minus:
        LEFT(newroot) = par_plusminus(LEFT(newroot));
      break;

      case times: case ptimes: case divide:
        LEFT(newroot) = par_timesdivide(LEFT(newroot));
      break;

      case power:
        LEFT(newroot) = par_pow(LEFT(newroot)); break;

      case transpose:
        LEFT(newroot) = par_trans(LEFT(newroot));
      break;

      case apply: case not:
        LEFT(newroot) = par_apply(LEFT(newroot));
      break;
    }
  }

  return newroot;
}
