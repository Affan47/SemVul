gfs2_jdata_writepage(struct page *page, struct writeback_control *wbc)
{
	struct inode *inode = page->mapping->host;
	struct gfs2_sbd *sdp = GFS2_SB(inode);
	int ret;
	int done_trans = 0;

	if (PageChecked(page)) {
		if (wbc->sync_mode != WB_SYNC_ALL)
			goto out_ignore;
		ret = gfs2_trans_begin(sdp, RES_DINODE + 1, 0);
		if (ret)
			goto out_ignore;
		done_trans = 1;
	}
	ret = gfs2_writepage_common(page, wbc);
	if (ret > 0)
		ret = __gfs2_jdata_writepage(page, wbc);
	if (done_trans)
		gfs2_trans_end(sdp);
	return ret;

out_ignore:
	redirty_page_for_writepage(wbc, page);
	unlock_page(page);
	return 0;
}
