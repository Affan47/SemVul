add_conjunct( const Effect& conjunct )
{
  const ConjunctiveEffect* conj_effect =
                              dynamic_cast<const ConjunctiveEffect*>(&conjunct);
  if( conj_effect != NULL )
    {
      for( EffectList::const_iterator ei = conj_effect->conjuncts_.begin();
	   ei != conj_effect->conjuncts_.end(); ++ei )
	{
	  Effect::register_use( *ei );
	  conjuncts_.push_back( *ei );
	}
      Effect::unregister_use( &conjunct );
    }
  else
    {
      conjuncts_.push_back( &conjunct );
    }
}
