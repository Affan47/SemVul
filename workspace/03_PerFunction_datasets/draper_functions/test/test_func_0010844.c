parseAll(SgmlParser &parser,
			 Messenger &mgr,
			 ArcDirector &director,
			 const volatile sig_atomic_t *cancelPtr)
{
  ArcEngineImpl wrap(mgr, &parser, director, cancelPtr,
		     0, Vector<StringC>(), 0);
  parser.parseAll(wrap, cancelPtr);
}
