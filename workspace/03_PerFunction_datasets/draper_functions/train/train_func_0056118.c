GRE_Reflow(GRE *gre,GResInfo *res) {
    if ( res->examples!=NULL &&
	    ( res->examples->creator==GHBoxCreate ||
	      res->examples->creator==GVBoxCreate ||
	      res->examples->creator==GHVBoxCreate ))
	GHVBoxReflow(res->examples->ret);
    GRE_RefreshAll(gre);
}
