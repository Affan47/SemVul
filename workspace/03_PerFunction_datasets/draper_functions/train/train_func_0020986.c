print_dlg_inner_structure(Block *block)
{
    Block *bpt = block, *b;

    for ( ; bpt != NULL; bpt = bpt->next) {

        if (!block_has_dlg_flg(bpt)
            && !block_has_car_tag(bpt)) {
            continue;
        }

        for (b = bpt->outer;
             block_has_dlg_flg(b->outer) || block_has_car_tag(b->outer);
             b = b->outer);

        for ( ;
              b != NULL && b->outer != bpt->outer;
              b = b->inner) {
            mfprintf(stdout, "%B\n", bpt);
        }

        mfprintf(stdout, "%B\n", bpt);

        if (bpt->inner) {
            print_dlg_inner_structure(bpt->inner);
        }
    }
}
