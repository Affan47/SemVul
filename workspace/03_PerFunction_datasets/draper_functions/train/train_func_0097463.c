flite_voice_add_lex_addenda(cst_voice *v, const cst_string *lexfile)
{

    cst_lexicon *lex;
    const cst_val *lex_addenda = NULL;
    cst_val *new_addenda;

    lex = val_lexicon(feat_val(v->features,"lexicon"));
    if (feat_present(v->features, "lex_addenda"))
	lex_addenda = feat_val(v->features, "lex_addenda");

    new_addenda = cst_lex_load_addenda(lex,lexfile);
#if 0
    printf("\naddenda: ");
    val_print(stdout,new_addenda);
    printf("\n");
#endif

    new_addenda = val_append(new_addenda,(cst_val *)lex_addenda);
    if (lex->lex_addenda)
        delete_val(lex->lex_addenda);
    lex->lex_addenda = new_addenda;

    return 0;
}
