elaborate_subscope_direct_(Design*des, NetScope*scope)
{
      typedef list<PGenerate*>::const_iterator generate_it_t;
      for (generate_it_t cur = generate_schemes.begin()
		 ; cur != generate_schemes.end() ; cur ++ ) {
	    (*cur) -> generate_scope(des, scope);
      }
}
