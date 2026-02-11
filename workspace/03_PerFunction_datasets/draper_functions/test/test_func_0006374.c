buildBranchList(AP_tree **&list, long &num, AP_BOOL create_terminal_branches, int deep) {
    if (deep>=0) {
        num = 2;
        for (int i=0; i<deep; i++) num *=2;
    }
    else {
        num = arb_tree_leafsum2() * (create_terminal_branches ? 2 : 1);
    }

    awt_assert(num >= 0);


    list = new AP_tree *[num*2+4];

    if (num) {
        long count = 0;

        buildBranchList_rek(this,list,count,create_terminal_branches,deep);
        list[count] = 0;
        num         = count/2;
    }
}
