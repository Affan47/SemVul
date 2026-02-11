_DoCVCompare(CharView *cv,int from,int to,double errbound) {
    if ( LayersSimilar(&cv->b.sc->layers[from],&cv->b.sc->layers[to],errbound))
	ff_post_notice(_("Match"),_("No significant differences found"));
    else
	ff_post_notice(_("Differ"),_("The layers do not match"));
}
