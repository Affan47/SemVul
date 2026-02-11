newFormTree(int pathSel, int oper,
                      char* varbName, vectr* elts) {
    formTree* nft = (formTree*) malloc(sizeof(formTree));
    const char* erreason = NULL;
    if(pathSel < EXISTS || pathSel > NONEPARA) erreason = "selector";
    if(oper < MNEXT || oper > MNONE) erreason = "operator";
    if(erreason != NULL) terror(-1, "Wrong %s type!\n", erreason, 0);

    nft->path_selector = pathSel;
    nft->opertr = oper;
    nft->varName = NULL;
    nft->elements = NULL;
    nft->left = NULL;
    nft->right = NULL;

    switch(pathSel) {
        case EXISTS:
        case ALWAYS:
            nft->elements = elts;
            break;
        case EXISTSPARA:
        case ALWAYSPARA:
        case NONEPARA:
            nft->varName = varbName;
            break;
        }

    return nft;
    }
