mthca_free_db(struct mthca_dev *dev, int type, int db_index)
{
	int i, j;
	struct mthca_db_page *page;

	i = db_index / MTHCA_DB_REC_PER_PAGE;
	j = db_index % MTHCA_DB_REC_PER_PAGE;

	page = dev->db_tab->page + i;

	mutex_lock(&dev->db_tab->mutex);

	page->db_rec[j] = 0;
	if (i >= dev->db_tab->min_group2)
		j = MTHCA_DB_REC_PER_PAGE - 1 - j;
	clear_bit(j, page->used);

	if (bitmap_empty(page->used, MTHCA_DB_REC_PER_PAGE) &&
	    i >= dev->db_tab->max_group1 - 1) {
		mthca_UNMAP_ICM(dev, mthca_uarc_virt(dev, &dev->driver_uar, i), 1);

		dma_free_coherent(&dev->pdev->dev, MTHCA_ICM_PAGE_SIZE,
				  page->db_rec, page->mapping);
		page->db_rec = NULL;

		if (i == dev->db_tab->max_group1) {
			--dev->db_tab->max_group1;

		}
		if (i == dev->db_tab->min_group2)
			++dev->db_tab->min_group2;
	}

	mutex_unlock(&dev->db_tab->mutex);
}
