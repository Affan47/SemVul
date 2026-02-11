write_ir_test_docs(Store *store)
{
    int i;
    Config config = default_config;
    IndexWriter *iw;
    Document **docs = prep_ir_test_docs();

    FieldInfos *fis = fis_new(STORE_YES, INDEX_YES,
                              TERM_VECTOR_WITH_POSITIONS_OFFSETS);
    fis_add_field(fis, fi_new("author", STORE_YES, INDEX_YES,
                              TERM_VECTOR_WITH_POSITIONS));
    fis_add_field(fis, fi_new("title", STORE_YES, INDEX_UNTOKENIZED,
                              TERM_VECTOR_WITH_OFFSETS));
    fis_add_field(fis, fi_new("year", STORE_YES, INDEX_UNTOKENIZED,
                              TERM_VECTOR_NO));
    fis_add_field(fis, fi_new("text", STORE_NO, INDEX_YES,
                              TERM_VECTOR_NO));
    index_create(store, fis);
    fis_deref(fis);
    config.max_buffered_docs = 5;

    iw = iw_open(store, whitespace_analyzer_new(false), &config);

    for (i = 0; i < IR_TEST_DOC_CNT; i++) {
        iw_add_doc(iw, docs[i]);
    }
    iw_close(iw);

    destroy_docs(docs, IR_TEST_DOC_CNT);
}
