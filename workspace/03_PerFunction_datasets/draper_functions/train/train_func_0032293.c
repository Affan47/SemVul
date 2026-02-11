cart_intonation(cst_utterance *u)
{
    cst_cart *accents, *tones;
    cst_item *s;
    const cst_val *v;

    if (feat_present(u->features,"no_intonation_accent_model"))
        return u;

    accents = val_cart(feat_val(u->features,"int_cart_accents"));
    tones = val_cart(feat_val(u->features,"int_cart_tones"));

    for (s=relation_head(utt_relation(u,"Syllable")); s; s=item_next(s))
    {
	v = cart_interpret(s,accents);
	if (!cst_streq("NONE",val_string(v)))
	    item_set_string(s,"accent",val_string(v));
	v = cart_interpret(s,tones);
	if (!cst_streq("NONE",val_string(v)))
	    item_set_string(s,"endtone",val_string(v));
	DPRINTF(0,("word %s gpos %s stress %s ssyl_in %s ssyl_out %s accent %s endtone %s\n",
		   ffeature_string(s,"R:SylStructure.parent.name"),
		   ffeature_string(s,"R:SylStructure.parent.gpos"),
		   ffeature_string(s,"stress"),
		   ffeature_string(s,"ssyl_in"),
		   ffeature_string(s,"ssyl_out"),
		   ffeature_string(s,"accent"),
		   ffeature_string(s,"endtone")));
    }

    return u;
}
