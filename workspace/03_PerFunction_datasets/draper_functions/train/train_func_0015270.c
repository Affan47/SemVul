operator-=(const Polynomial &p)
{
  if(p.terms.empty())return;
  if(p.getSugar()>sugar)sugar=p.getSugar();


  TermMap::iterator i=terms.lower_bound(p.terms.begin()->first);

  for(TermMap::const_iterator j=p.terms.begin();j!=p.terms.end();j++)
    {
      while(i!=terms.end() && (terms.value_comp()(*i,*j)))i++;
      if(i==terms.end())
	{
	  terms.insert(i,TermMap::value_type(j->first,-j->second));
	}
      else
	{
	  if(!terms.value_comp()(*j,*i))
	    {
	      FieldElement c=i->second-j->second;
	      if(c.isZero())
		{

		  TermMap::iterator oldI=i;
		  i++;
		  terms.erase(oldI);
		}
	      else
		{
		  i->second=c;
		}
	    }
	  else
	    {
	      terms.insert(i,TermMap::value_type(j->first,-j->second));
	    }
	}
    }


}
