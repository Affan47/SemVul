queue_variant_definition(name, macros)
char *name ;
struct stringlist *macros ;
{


    struct stringlist *mac ;
    struct stringlist *pr_mac ;


    int curvdef ;
    int curmdef ;


    for (curvdef = 0;
	 variantDefs[curvdef].name != NULL && curvdef < MAXVARDEFS;
	 curvdef++) {

	if (!strcmp (variantDefs[curvdef].name, name)) {

	    errexit (33, name) ;
	}
    }
    if (curvdef == MAXVARDEFS) {

	errexit (27, "variant definitions") ;
    }


    lastVariantDef = curvdef ;


    variantDefs[curvdef].name = name ;
    variantDefs[curvdef].vpath = NULL ;
    variantDefs[curvdef].vflags = NULL ;
    for(curmdef = 0; curmdef < MAXVMACROS; curmdef++) {
	variantDefs[curvdef].vmacros[curmdef] = NULL ;
    }


    variantDefs[curvdef + 1].name = NULL ;


    curmdef = 0 ;
    for (mac = macros, pr_mac = NULL;
	 mac != NULL;
	 pr_mac = mac, mac = mac->next) {

	char *macname ;
	char *macptr ;
	char *macval ;

	if (pr_mac != NULL) {
	    free(pr_mac) ;
	}


	macptr = mac->string ;
	macname = get_name(&macptr) ;

	macptr = skip_over_whitespace(macptr) ;


	if (*macptr != '=') {
	    parsing_error("\"=\" expected in variant definition",
			  macptr, name) ;
	}
	macval = macptr = skip_over_whitespace(macptr + 1) ;


	if (*macval && !strcmp(macname, "vpath")) {
	    char *cp ;


	    if (!strcmp((cp = get_name(&macval)), "..") &&

		*skip_over_whitespace(macval) == '\0') {
		variantDefs[curvdef].vpath = check_strdup(prev_dir) ;
	    } else {

		variantDefs[curvdef].vpath = macptr ;
	    }
	    free(cp) ;
	} else if (*macval && !strcmp(macname, "vflags")) {
	    variantDefs[curvdef].vflags = macval ;
	} else {


	    if (curmdef >= MAXVMACROS) {
		fatal("too many variant macro definitions", name) ;
	    }


	    variantDefs[curvdef].vmacros[curmdef++] = mac->string ;
	}
	free(macname) ;
    }
    free(pr_mac) ;

    vardef_end() ;

}
