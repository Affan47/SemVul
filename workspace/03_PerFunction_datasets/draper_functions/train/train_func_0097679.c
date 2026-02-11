cleanuplofig(lofig_list *f)
{
locon_list *c;
chain_list *n;

    for (c = f->LOCON; c != NULL; c = c->NEXT) {
        n = addchain(NULL, c->NAME);
        freechain(c->SIG->NAMECHAIN);
        c->SIG->NAMECHAIN = n;
    }
}
