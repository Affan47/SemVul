page_zip_copy_recs(

	page_zip_des_t*		page_zip,


	page_t*			page,
	const page_zip_des_t*	src_zip,
	const page_t*		src,
	dict_index_t*		index,
	mtr_t*			mtr)
{
	ut_ad(mtr_memo_contains_page(mtr, page, MTR_MEMO_PAGE_X_FIX));
	ut_ad(mtr_memo_contains_page(mtr, src, MTR_MEMO_PAGE_X_FIX));
	ut_ad(!dict_index_is_ibuf(index));
#ifdef UNIV_ZIP_DEBUG


	ut_a(page_zip_validate_low(src_zip, src, index, TRUE));
#endif
	ut_a(page_zip_get_size(page_zip) == page_zip_get_size(src_zip));
	if (UNIV_UNLIKELY(src_zip->n_blobs)) {
		ut_a(page_is_leaf(src));
		ut_a(dict_index_is_clust(index));
	}


	ut_a(dict_index_is_clust(index) || !page_is_leaf(src)
	     || page_get_max_trx_id(src));

	UNIV_MEM_ASSERT_W(page, UNIV_PAGE_SIZE);
	UNIV_MEM_ASSERT_W(page_zip->data, page_zip_get_size(page_zip));
	UNIV_MEM_ASSERT_RW(src, UNIV_PAGE_SIZE);
	UNIV_MEM_ASSERT_RW(src_zip->data, page_zip_get_size(page_zip));


#if PAGE_MAX_TRX_ID + 8 != PAGE_HEADER_PRIV_END
# error "PAGE_MAX_TRX_ID + 8 != PAGE_HEADER_PRIV_END"
#endif
	memcpy(PAGE_HEADER + page, PAGE_HEADER + src,
	       PAGE_HEADER_PRIV_END);
	memcpy(PAGE_DATA + page, PAGE_DATA + src,
	       UNIV_PAGE_SIZE - PAGE_DATA - FIL_PAGE_DATA_END);
	memcpy(PAGE_HEADER + page_zip->data, PAGE_HEADER + src_zip->data,
	       PAGE_HEADER_PRIV_END);
	memcpy(PAGE_DATA + page_zip->data, PAGE_DATA + src_zip->data,
	       page_zip_get_size(page_zip) - PAGE_DATA);


	{
		page_zip_t*	data = page_zip->data;
		memcpy(page_zip, src_zip, sizeof *page_zip);
		page_zip->data = data;
	}
	ut_ad(page_zip_get_trailer_len(page_zip, dict_index_is_clust(index))
	      + page_zip->m_end < page_zip_get_size(page_zip));

	if (!page_is_leaf(src)
	    && UNIV_UNLIKELY(mach_read_from_4(src + FIL_PAGE_PREV) == FIL_NULL)
	    && UNIV_LIKELY(mach_read_from_4(page
					    + FIL_PAGE_PREV) != FIL_NULL)) {

		ulint	offs = rec_get_next_offs(page + PAGE_NEW_INFIMUM,
						 TRUE);
		if (UNIV_LIKELY(offs != PAGE_NEW_SUPREMUM)) {
			rec_t*	rec = page + offs;
			ut_a(rec[-REC_N_NEW_EXTRA_BYTES]
			     & REC_INFO_MIN_REC_FLAG);
			rec[-REC_N_NEW_EXTRA_BYTES] &= ~ REC_INFO_MIN_REC_FLAG;
		}
	}

#ifdef UNIV_ZIP_DEBUG
	ut_a(page_zip_validate(page_zip, page, index));
#endif
	btr_blob_dbg_add(page, index, "page_zip_copy_recs");

	page_zip_compress_write_log(page_zip, page, index, mtr);
}
