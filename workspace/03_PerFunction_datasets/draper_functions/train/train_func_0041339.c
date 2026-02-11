generate_limit4(typedecl * d, char * var, typedecl * e)
{
  stelist * t;
  typedecl * d2;

  if (e->gettypeclass() == typedecl::Scalarset
      && e == d)
    generate_limit4(d->getsize(), d->mu_name, var, d->getleft(),FALSE);
  else if (e->gettypeclass() == typedecl::Union
	   && ((uniontypedecl *)e)->IsUnionWithScalarset())
    {
      for(t=((uniontypedecl *)e)->getunionmembers();
	  t!= NULL; t=t->next)
	{
	  d2 = (typedecl *)t->s->getvalue();
	  if (d2 == d)
	    fprintf(codefile,
		    "\n"
		    "      // refinement -- graph structure for a single scalarset\n"
		    "      //               as in array S1 of S1\n"
		    "      // only if there is more than 1 permutation in class\n"
		    "      if (Perm.MTO_class_%s() && count_%s<%d)\n"
		    "        {\n"
		    "          exists = FALSE;\n"
		    "          split = FALSE;\n"
		    "          for (k=0; k<%d; k++) // step through class\n"
		    "            if (!(*this)[k+%d]%s.isundefined()\n"
		    "                &&(*this)[k+%d]%s!=k+%d\n"
		    "                &&(*this)[k+%d]%s>=%d\n"
		    "                &&(*this)[k+%d]%s<=%d)\n"
		    "              exists = TRUE;\n"
		    "          if (exists)\n"
		    "            {\n"
		    "              for (i=0; i<count_%s; i++) // for value priority\n"
		    "                {\n"
		    "                  for (j=0; j<count_%s; j++) // for value priority\n"
		    "                    {\n"
		    "                      exists = FALSE;\n"
		    "                      for (k=0; k<%d; k++) // step through class\n"
		    "                        goodset_%s[k] = FALSE;\n"
		    "                      for (k=0; k<%d; k++) // step through class\n"
		    "                        if (pos_%s[i][k] \n"
		    "                            && !(*this)[k+%d]%s.isundefined()\n"
		    "                            && (*this)[k+%d]%s!=k+%d\n"
		    "                            && (*this)[k+%d]%s>=%d\n"
		    "                            && (*this)[k+%d]%s<=%d\n"
		    "                            && pos_%s[j][(*this)[k+%d]%s-%d])\n"
		    "                          {\n"
		    "                            exists = TRUE;\n"
		    "                            goodset_%s[k] = TRUE;\n"
		    "                          }\n"
		    "                      if (exists)\n"
		    "                        {\n"
		    "                          split=FALSE;\n"
		    "                          for (k=0; k<%d; k++)\n"
		    "                            if ( pos_%s[i][k] && !goodset_%s[k] ) \n"
		    "                              split= TRUE;\n"
		    "                          if (split)\n"
		    "                            {\n"
		    "                              for (j=count_%s; j>i; j--)\n"
		    "                                for (k=0; k<%d; k++)\n"
		    "                                  pos_%s[j][k] = pos_%s[j-1][k];\n"
		    "                              for (k=0; k<%d; k++)\n"
		    "                                {\n"
		    "                                  if (pos_%s[i][k] && !goodset_%s[k])\n"
		    "                                    pos_%s[i][k] = FALSE;\n"
		    "                                  if (pos_%s[i+1][k] && goodset_%s[k])\n"
		    "                                    pos_%s[i+1][k] = FALSE;                  \n"
		    "                                }\n"
		    "                              count_%s++;\n"
		    "                            }\n"
		    "                        }\n"
		    "                    }\n"
		    "                }\n"
		    "            }\n"
		    "        }\n",
		    d->mu_name, d->mu_name, d->getsize(),
		    d->getsize(),
		    d->getleft(), var,
		    d->getleft(), var, d->getleft(),
		    d->getleft(), var, d->getleft(),
		    d->getleft(), var, d->getright(),

		    d->mu_name,
		    d->mu_name,
		    d->getsize(), d->mu_name,
		    d->getsize(),
		    d->mu_name,
		    d->getleft(), var,
		    d->getleft(), var, d->getleft(),
		    d->getleft(), var, d->getleft(),
		    d->getleft(), var, d->getright(),
		    d->mu_name, d->getleft(), var, d->getleft(),
		    d->mu_name,

		    d->getsize(),
		    d->mu_name, d->mu_name,
		    d->mu_name,
		    d->getsize(),
		    d->mu_name, d->mu_name,
		    d->getsize(),

		    d->mu_name, d->mu_name,
		    d->mu_name,
		    d->mu_name, d->mu_name,
		    d->mu_name,
		    d->mu_name
		    );
	}
    }
}
