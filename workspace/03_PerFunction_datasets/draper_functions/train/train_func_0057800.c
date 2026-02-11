test_allocate_split(void)
{
    H5MP_pool_t *mp;
    size_t free_size;
    void *spc1;
    void *spc2;


    TESTING("splitting block in pool");


    if(NULL == (mp = H5MP_create((size_t)MPOOL_PAGE_SIZE, MPOOL_FLAGS)))
        TEST_ERROR


    if(NULL == (spc1 = H5MP_malloc(mp, (size_t)MPOOL_NORMAL_BLOCK)))
        TEST_ERROR


    if(H5MP_get_pool_free_size(mp, &free_size) < 0)
        TEST_ERROR
    if(free_size != MPOOL_PAGE_SIZE - (H5MP_BLOCK_ALIGN(MPOOL_NORMAL_BLOCK) + H5MP_BLOCK_ALIGN(sizeof(H5MP_page_blk_t)) + H5MP_BLOCK_ALIGN(sizeof(H5MP_page_t))))
        TEST_ERROR


    if(H5MP_pool_is_free_size_correct(mp) <= 0)
        TEST_ERROR


    if(NULL == (spc2 = H5MP_malloc(mp, (size_t)MPOOL_NORMAL_BLOCK)))
        TEST_ERROR


    if(H5MP_get_pool_free_size(mp, &free_size) < 0)
        TEST_ERROR
    if(free_size != MPOOL_PAGE_SIZE - (((H5MP_BLOCK_ALIGN(MPOOL_NORMAL_BLOCK) + H5MP_BLOCK_ALIGN(sizeof(H5MP_page_blk_t))) * 2) + H5MP_BLOCK_ALIGN(sizeof(H5MP_page_t))))
        TEST_ERROR


    if(H5MP_pool_is_free_size_correct(mp) <= 0)
        TEST_ERROR


    H5MP_free(mp, spc1);


    if(H5MP_get_pool_free_size(mp, &free_size) < 0)
        TEST_ERROR
    if(free_size != MPOOL_PAGE_SIZE - (H5MP_BLOCK_ALIGN(MPOOL_NORMAL_BLOCK) + H5MP_BLOCK_ALIGN(sizeof(H5MP_page_blk_t)) + H5MP_BLOCK_ALIGN(sizeof(H5MP_page_t))))
        TEST_ERROR


    if(H5MP_pool_is_free_size_correct(mp) <= 0)
        TEST_ERROR


    H5MP_free(mp, spc2);


    if(H5MP_get_pool_free_size(mp, &free_size) < 0)
        TEST_ERROR
    if(free_size != MPOOL_PAGE_SIZE - H5MP_BLOCK_ALIGN(sizeof(H5MP_page_t)))
        TEST_ERROR


    if(H5MP_pool_is_free_size_correct(mp) <= 0)
        TEST_ERROR


    if(H5MP_close(mp) < 0)
        TEST_ERROR

    PASSED();

    return 0;

error:
    H5E_BEGIN_TRY {
        if(mp)
            H5MP_close(mp);
    } H5E_END_TRY;

    return 1;
}
