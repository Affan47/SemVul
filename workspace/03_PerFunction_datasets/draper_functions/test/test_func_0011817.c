multi_decls (bool print)
{


  pIIR_Declaration d = NULL;
  for (int i = 0; i < n_decls; i++)
    if (decls[i].state == valid)
      return true;

  if (print && name && pr)
    {

      if (n_decls == 0)
	pr->error ("%:%n is undeclared", name, name);
      else
	{

	  pr->error ("%:use of %n is ambigous, candidates are", name, name);
	  show (!(pr && pr->options.debug));
	}
    }
  return false;
}
