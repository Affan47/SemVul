rewrite(rview kc_current_view_base)
{
    if (is_nil()) {
	return this;
    } else {
	patternchain l_patternchain_1 =
	    patternchain_1->rewrite(kc_current_view_base);
	patternchains l_patternchains_1 =
	    patternchains_1->rewrite(kc_current_view_base);
	switch(kc_current_view_base) {
	    default:
	    case base_rview_enum: {
		base_rview_class& kc_current_view=static_cast<base_rview_class&>(kc_current_view_base);
		if ((l_patternchain_1->prod_sel() == sel_Conspatternchain) && ((l_patternchain_1)->patternchainitem_1->prod_sel() == sel_PatternchainitemGroup) && ((l_patternchain_1)->patternchain_1->prod_sel() == sel_Nilpatternchain) && (l_patternchains_1->prod_sel() == sel_Nilpatternchains)) { KC_TRACE_REWRITE_MATCH(kc_current_view, "util.k", 341, this);
		    const patternchains P_pcs = phylum_cast<const impl_patternchainitem_PatternchainitemGroup*>((l_patternchain_1)->patternchainitem_1)->patternchains_1;
		    patternchains kc_result = P_pcs;

		    KC_TRACE_REWRITE_RESULT(kc_current_view,"util.k",342,kc_result);
		    return (const_cast<const impl_patternchains*>(kc_result) == this) ? this : kc_result->rewrite( kc_current_view_base );

		} else
		    if ((l_patternchain_1->prod_sel() == sel_Conspatternchain) && ((l_patternchain_1)->patternchainitem_1->prod_sel() == sel_PatternchainitemGroup) && ((l_patternchain_1)->patternchain_1->prod_sel() == sel_Nilpatternchain) && (l_patternchains_1->prod_sel() == sel_Conspatternchains)) { KC_TRACE_REWRITE_MATCH(kc_current_view, "util.k", 352, this);
		    const patternchains P_pcs = phylum_cast<const impl_patternchainitem_PatternchainitemGroup*>((l_patternchain_1)->patternchainitem_1)->patternchains_1;
		    const patternchains Q_pcs = l_patternchains_1;
		    patternchains kc_result = concat(P_pcs, Q_pcs);

		    KC_TRACE_REWRITE_RESULT(kc_current_view,"util.k",353,kc_result);
		    return (const_cast<const impl_patternchains*>(kc_result) == this) ? this : kc_result->rewrite( kc_current_view_base );

		} else
		    break;    }
	}
	if ((l_patternchain_1 == patternchain_1) &&  (l_patternchains_1 == patternchains_1))
	    return this;
	else {
	    impl_patternchains* kc_result= Conspatternchains(l_patternchain_1, l_patternchains_1);
	    kc_result->rewrite_members(this);
	    return kc_result;
	}   }
}
