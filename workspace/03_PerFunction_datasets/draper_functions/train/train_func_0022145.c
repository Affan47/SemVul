analyze( PredicateTable &predicates, TermTable &terms,
			 std::map<const StateFormula*,const Atom*> &hash ) const
{
  for( EffectList::const_iterator ei = conjuncts_.begin();
                                                  ei != conjuncts_.end(); ++ei )
    (*ei)->analyze( predicates, terms, hash );
}
