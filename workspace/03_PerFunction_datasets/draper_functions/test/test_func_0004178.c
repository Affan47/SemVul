S_new_he(pTHX)
{
    dVAR;
    HE* he;
    void ** const root = &PL_body_roots[HE_SVSLOT];

    if (!*root)
	Perl_more_bodies(aTHX_ HE_SVSLOT, sizeof(HE), PERL_ARENA_SIZE);
    he = (HE*) *root;
    assert(he);
    *root = HeNEXT(he);
    return he;
}
