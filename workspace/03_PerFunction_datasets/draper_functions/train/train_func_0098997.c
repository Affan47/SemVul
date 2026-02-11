displayFormTree(formTree* ftree) {
    while(1) {
        if(ftree == NULL) {
            printf("Null formula, going up!\n");
            return;
            }

        if(ftree->path_selector == EXISTS || ftree->path_selector == ALWAYS ||
                ftree->path_selector == EXISTSPARA || ftree->path_selector == ALWAYSPARA) {

            if(ftree->path_selector == EXISTS || ftree->path_selector == EXISTSPARA) printf("E");
            else printf("A");

            switch(ftree->opertr) {
                case MNEXT:
                    printf("X( ");
                    break;
                case MGLOBALLY:
                    printf("G( ");
                    break;
                case MFUTURE:
                    printf("F( ");
                    break;
                case MGLOBALLYOM:
                    printf("Gom( ");
                    break;
                case MUNTIL:
                    printf("U( ");
                    break;
                default:
                    terror(-1, "Modal: wrong operator here: %d\n", NULL, ftree->opertr);
                }

            if(ftree->path_selector == EXISTS || ftree->path_selector == ALWAYS) {
                int i = 0;
                for(i = 0; i < (ftree->elements)->elements; ++i)
                    printf("%s ", (char*) get(ftree->elements, i));
                }
            else printf("$%s ", ftree->varName);

            }
        else if(ftree->path_selector == NONEPARA && (ftree->opertr == BNOT || ftree->opertr == BAND
                || ftree->opertr == BOR || ftree->opertr == MNONE)) {

            switch(ftree->opertr) {
                case BNOT:
                    printf("NOT(");
                    break;
                case BAND:
                    printf("AND(");
                    break;
                case BOR:
                    printf("OR(");
                    break;
                case MNONE:
                    printf("(%s",ftree->varName);
                    break;
                default:
                    terror(-1, "Boolean: wrong operator here: %d\n", NULL, ftree->path_selector);
                }

            }
        else terror(-1, "Wrong selector here: %d\n", NULL, ftree->path_selector);
        printf(")\n");

        printf("Select 0-up, 1-left, 2-right, q for quit\n");
        unsigned char answ = getchar();
        getchar();
        if(answ == '0') return;
        else if(answ == '1') displayFormTree(ftree->left);
        else if(answ == '2') displayFormTree(ftree->right);
        else exit(0);
        }

    }
