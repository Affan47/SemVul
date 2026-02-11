deleteFormula( formula_t *formula )
 {
   register idList_t *var, *pvar, *nvar;

   if( formula != NULL )
     {
       switch( formula->type )
	 {
	 case ATOMIC_FORMULA:
	   free( formula->u.atomic );
	   break;
	 case WHEN_FORMULA:
	   deleteFormula( formula->u.when.condition );
	   deleteFormula( formula->u.when.addEffect );
	   deleteFormula( formula->u.when.delEffect );
	   break;
	 case FORALL_FORMULA:
	   for( pvar = NULL, var = formula->u.forall.vars; var != NULL; var = nvar )
	     {
	       nvar = var->next;
	       free( var );
	     }
	   deleteFormula( formula->u.forall.addEffect );
	   deleteFormula( formula->u.forall.delEffect );
	   deleteFormula( formula->u.forall.whenEffect );
	   break;
	 }
       free( formula );
     }
}
