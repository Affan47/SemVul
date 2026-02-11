test_skiplist_remove_many(void)
{
    H5SL_t *slist;
    size_t num;
    size_t u;
    int *found_item;
    herr_t ret;


    MESSAGE(7, ("Testing Removal of Many Items From Skip List\n"));


    slist = H5SL_create(H5SL_TYPE_INT, NULL);
    CHECK(slist, NULL, "H5SL_create");


    num=H5SL_count(slist);
    VERIFY(num, 0, "H5SL_count");


    for(u=0; u<NUM_ELEMS; u++) {
        ret=H5SL_insert(slist,&rand_num[u],&rand_num[u]);
        CHECK(ret, FAIL, "H5SL_insert");
    }


    num=H5SL_count(slist);
    VERIFY(num, NUM_ELEMS, "H5SL_count");


    for(u=0; u<NUM_ELEMS; u++) {
        found_item=(int *)H5SL_remove(slist,&rand_num[u]);
        CHECK(found_item, NULL, "H5SL_remove");
        VERIFY(*found_item,rand_num[u],"H5SL_remove");
    }


    num=H5SL_count(slist);
    VERIFY(num, 0, "H5SL_count");


    for(u=0; u<NUM_ELEMS; u++) {
        ret=H5SL_insert(slist,&rand_num[u],&rand_num[u]);
        CHECK(ret, FAIL, "H5SL_insert");
    }


    num=H5SL_count(slist);
    VERIFY(num, NUM_ELEMS, "H5SL_count");


    for(u=0; u<NUM_ELEMS; u++) {
        found_item=(int *)H5SL_remove(slist,&sort_rand_num[u]);
        CHECK(found_item, NULL, "H5SL_remove");
        VERIFY(*found_item,sort_rand_num[u],"H5SL_remove");
    }


    num=H5SL_count(slist);
    VERIFY(num, 0, "H5SL_count");


    for(u=0; u<NUM_ELEMS; u++) {
        ret=H5SL_insert(slist,&rand_num[u],&rand_num[u]);
        CHECK(ret, FAIL, "H5SL_insert");
    }


    num=H5SL_count(slist);
    VERIFY(num, NUM_ELEMS, "H5SL_count");


    for(u=0; u<NUM_ELEMS; u++) {
        found_item=(int *)H5SL_remove(slist,&rev_sort_rand_num[u]);
        CHECK(found_item, NULL, "H5SL_remove");
        VERIFY(*found_item,rev_sort_rand_num[u],"H5SL_remove");
    }


    num=H5SL_count(slist);
    VERIFY(num, 0, "H5SL_count");


    ret=H5SL_close(slist);
    CHECK(ret, FAIL, "H5SL_close");

}
