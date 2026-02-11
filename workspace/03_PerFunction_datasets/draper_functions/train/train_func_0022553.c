getRandomNodes(int anzahl) {


    AP_tree **list;
    AP_tree **retlist;
    long num;
    long count = 0,i =0;

    long sumnodes;
    if (!anzahl) return 0;
    buildNodeList(list,sumnodes);
    if (!sumnodes) {
        delete list;
        return 0;
    }

    retlist = (AP_tree **)calloc(anzahl,sizeof(AP_tree *));

    i = 0;
    count = sumnodes;
    for  (i=0; i< anzahl; i++) {
        num = GB_random(count);

        retlist[i] = list[num];
        count--;

        list[num]   = list[count];
        list[count] = retlist[i];

        if (count == 0) count = sumnodes;
    }
    delete list;
    return retlist;
}
