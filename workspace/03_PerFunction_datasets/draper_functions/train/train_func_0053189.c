Scm_MakeGClosure_mmc(ScmProcedure *procedure,ScmObj name)
{
    GClosure *c = g_closure_new_simple(sizeof(SClosure), NULL);
    ((SClosure*)c)->proc = procedure;
    Scm_GtkProtect(SCM_OBJ(procedure));
    g_closure_add_finalize_notifier(c, (gpointer)procedure,
                                    Scm_GClosureDestroy);


    ScmModule *module = SCM_MODULE(SCM_FIND_MODULE("gtk", TRUE));
    ScmSymbol *symbol = SCM_SYMBOL(SCM_INTERN("gpointer-mapping"));

#if mmc_debug
    if (symbol)
       Scm_Warn("%s: found the symbol",  __FUNCTION__);
#endif

    ScmObj mapping = Scm_SymbolValue(module, symbol);

#if mmc_debug
    if (mapping && (SCM_HASHTABLEP(mapping)))
       Scm_Warn("%s: found the value, too, Now searching for %s",  __FUNCTION__, Scm_GetStringConst(SCM_STRING(name)));
#endif


    ScmHashEntry* e = Scm_HashTableGet(SCM_HASHTABLE(mapping), name);

    if (mapping && (SCM_HASHTABLEP(mapping)) &&

        (e))
       {


          if (SCM_PAIRP(e->value)
              && SCM_INTEGERP(SCM_CAR(e->value))
              && SCM_STRINGP(SCM_CDR(e->value)))
             {


                ((SClosure*)c)->gpointers = Scm_GetInteger(SCM_CAR(e->value));

                ((SClosure*)c)->gpointer_mapping = Scm_GetString(SCM_STRING(SCM_CDR(e->value)));

                g_closure_set_marshal(c, Scm_mmc_GClosureMarshal);
                goto end;
             }
       };

    ((SClosure*)c)->gpointers = 0;
    g_closure_set_marshal(c, Scm_GClosureMarshal);

  end:
    return c;
}
