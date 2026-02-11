show_noun(int n)
{
    int adj,*p;


    for (p = adjectives[n-1], adj = FALSE; *p; p++, adj = TRUE) {
	if (adj) trm_chr(' ');
	trm_str(wtext[anums[p-adjs]]);
    }


    if (adj) trm_chr(' ');
    trm_str(wtext[nnums[n-1]]);
}
