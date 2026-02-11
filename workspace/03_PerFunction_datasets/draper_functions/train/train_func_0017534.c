test_skiplist_insert(void)
{
    H5SL_t *slist;
    int key,
        item;
    int search_key;
    int *found_item;
    size_t num;
    herr_t ret;


    MESSAGE(7, ("Testing Insertion Into Skip List\n"));


    slist = H5SL_create(H5SL_TYPE_INT, NULL);
    CHECK(slist, NULL, "H5SL_create");


    num=H5SL_count(slist);
    VERIFY(num, 0, "H5SL_count");


    key=37;
    found_item=(int *)H5SL_search(slist,&key);
    VERIFY(found_item, NULL, "H5SL_search");


    key=2; item=10;
    ret=H5SL_insert(slist,&item,&key);
    CHECK(ret, FAIL, "H5SL_insert");


    num=H5SL_count(slist);
    VERIFY(num, 1, "H5SL_count");


    found_item=(int *)H5SL_search(slist,&key);
    CHECK(found_item, NULL, "H5SL_search");
    VERIFY(*found_item,item,"H5SL_search");


    search_key=37;
    found_item=(int *)H5SL_search(slist,&search_key);
    VERIFY(found_item, NULL, "H5SL_search");


    search_key=2;
    ret=H5SL_insert(slist,&search_key,&search_key);
    VERIFY(ret, FAIL, "H5SL_insert");


    ret=H5SL_close(slist);
    CHECK(ret, FAIL, "H5SL_close");

}
