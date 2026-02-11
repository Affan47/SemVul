urltrans_add_one(URLTranslationList *trans, CfgGroup *grp)
{
    URLTranslation *ot;
    List *list2;

    ot = create_onetrans(grp);
    if (ot == NULL)
	return -1;

    if (ot->type != TRANSTYPE_SENDSMS && ot->keyword_regex == NULL)
        gwlist_append(trans->defaults, ot);
    else
        gwlist_append(trans->list, ot);

    list2 = dict_get(trans->names, ot->name);
    if (list2 == NULL) {
    	list2 = gwlist_create();
	dict_put(trans->names, ot->name, list2);
    }
    gwlist_append(list2, ot);

    return 0;
}
