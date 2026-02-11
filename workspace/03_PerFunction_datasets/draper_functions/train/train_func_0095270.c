cross_products( std::list<const Disjunction*>::const_iterator it,
			     std::list<const Disjunction*>::const_iterator end,
			     std::list<const StateFormula*> &flist,
			     std::list<const Conjunction*> &xproduct )
{
  if( it == end )
    {
      Conjunction *conj = new Conjunction;
      for( std::list<const StateFormula*>::const_iterator i = flist.begin(); i != flist.end(); ++i )
	{
	  if( dynamic_cast<const Conjunction*>( (*i) ) )
	    {
	      const Conjunction *f = (const Conjunction*)(*i);
	      for( size_t j = 0; j < f->size(); ++j )
		{
		  StateFormula::register_use( &f->conjunct( j ) );
		  conj->add_conjunct( f->conjunct( j ) );
		}
	    }
	  else
	    {
	      StateFormula::register_use( (*i) );
	      conj->add_conjunct( *(*i) );
	    }
	}
      xproduct.push_back( conj );
    }
  else
    {
      for( size_t i = 0; i < (*it)->size(); ++i )
	{
	  flist.push_back( &(*it)->disjunct( i ) );
	  ++it;
	  cross_products( it, end, flist, xproduct );
	  --it;
	  flist.pop_back();
	}
    }
}
