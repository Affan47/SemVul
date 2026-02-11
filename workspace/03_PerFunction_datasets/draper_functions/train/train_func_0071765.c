prepare_search_index(Store *store)
{
    int i;
    IndexWriter *iw;
    struct Data data[SEARCH_DOCS_SIZE] = {
        {"20050930", "word1",
            "cat1/"},
        {"20051001", "word1 word2 the quick brown fox",
            "cat1/sub1"},
        {"20051002", "word1 word3",
            "cat1/sub1/subsub1"},
        {"20051003", "word1 word3",
            "cat1/sub2"},
        {"20051004", "word1 word2",
            "cat1/sub2/subsub2"},
        {"20051005", "word1",
            "cat2/sub1"},
        {"20051006", "word1 word3",
            "cat2/sub1"},
        {"20051007", "word1",
            "cat2/sub1"},
        {"20051008", "word1 word2 word3 the fast brown fox",
            "cat2/sub1"},
        {"20051009", "word1",
            "cat3/sub1"},
        {"20051010", "word1",
            "cat3/sub1"},
        {"20051011", "word1 word3 the quick red fox",
            "cat3/sub1"},
        {"20051012", "word1",
            "cat3/sub1"},
        {"20051013", "word1",
            "cat1/sub2"},
        {"20051014", "word1 word3 the quick hairy fox",
            "cat1/sub1"},
        {"20051015", "word1",
            "cat1/sub2/subsub1"},
        {"20051016", "word1 the quick fox is brown and hairy and a little red",
            "cat1/sub1/subsub2"},
        {"20051017", "word1 the brown fox is quick and red",
            "cat1/"}
    };

    FieldInfos *fis = fis_new(STORE_YES, INDEX_YES, TERM_VECTOR_YES);
    index_create(store, fis);
    fis_deref(fis);

    iw = iw_open(store, dbl_analyzer_new(false), NULL);
    for (i = 0; i < SEARCH_DOCS_SIZE; i++) {
        Document *doc = doc_new();
        doc->boost = (float)(i+1);
        doc_add_field(doc, df_add_data(df_new(date), data[i].date));
        doc_add_field(doc, df_add_data(df_new(field), data[i].field));
        doc_add_field(doc, df_add_data(df_new(cat), data[i].cat));
        iw_add_doc(iw, doc);
        doc_destroy(doc);
    }
    iw_close(iw);
}
