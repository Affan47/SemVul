is_defined_recipe(const recipe *rp, const object *cauldron, object *caster) {
    uint32 batches_in_cauldron;
    const linked_char *ingredient;
    int number;


    number = 0;
    for (ingredient = rp->ingred; ingredient != NULL; ingredient = ingredient->next)
        number++;
    FOR_INV_PREPARE(cauldron, ob)
        number--;
    FOR_INV_FINISH();
    if (number != 0)
        return 0;


    batches_in_cauldron = 0;
    for (ingredient = rp->ingred; ingredient != NULL; ingredient = ingredient->next) {
        uint32 nrof;
        const char *name;
        int ok;


        name = ingredient->name;
        nrof = 0;
        while (isdigit(*name)) {
            nrof = 10*nrof+(*name-'0');
            name++;
        }
        if (nrof == 0)
            nrof = 1;
        while (*name == ' ')
            name++;


        ok = 0;
        FOR_INV_PREPARE(cauldron, ob) {
            char name_ob[MAX_BUF];
            const char *name2;

            if (ob->title == NULL)
                name2 = ob->name;
            else {
                snprintf(name_ob, sizeof(name_ob), "%s %s", ob->name, ob->title);
                name2 = name_ob;
            }

            if (strcmp(name2, name) == 0) {
                if (ob->nrof%nrof == 0) {
                    uint32 batches;

                    batches = ob->nrof/nrof;
                    if (batches_in_cauldron == 0) {
                        batches_in_cauldron = batches;
                        ok = 1;
                    } else if (batches_in_cauldron == batches)
                        ok = 1;
                }
                break;
            }
        } FOR_INV_FINISH();
        if (!ok)
            return(0);
    }

    return(1);
}
