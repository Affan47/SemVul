kc_initialize_includefile
#ifdef KC_USE_PROTOTYPES
(includefile kc_x)
#else
(kc_x) includefile kc_x;
#endif
{
#line 212 "../abs.k"
	kc_x->inc_type =  include_unknown;
#line 214 "../abs.k"
	kc_x->newinclude =  0;
#line 215 "../abs.k"
 kc_x->inc[0] = Nilincludedeclarations();
	  kc_x->inc[1] = Nilincludedeclarations();
	 if (Theincludefiles == (includefiles)0) {
	     Theincludefiles = Consincludefiles( kc_x, Nilincludefiles());
	  } else {
	     Theincludefiles = Consincludefiles( kc_x, Theincludefiles);
	  }

#line 5599 "k.c"

#line 5601 "k.c"
	return kc_x;
}
