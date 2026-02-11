draw_pobs(int page)
{
	int c1;
	int back_buf_ofs;

	back_buf_ofs = 0;

	for (c1 = main_info.page_info[page].num_pobs - 1; c1 >= 0; c1--) {
		main_info.page_info[page].pobs[c1].back_buf_ofs = back_buf_ofs;
		get_block(page, main_info.page_info[page].pobs[c1].x - pob_hs_x(main_info.page_info[page].pobs[c1].image, main_info.page_info[page].pobs[c1].pob_data), main_info.page_info[page].pobs[c1].y - pob_hs_y(main_info.page_info[page].pobs[c1].image, main_info.page_info[page].pobs[c1].pob_data), pob_width(main_info.page_info[page].pobs[c1].image, main_info.page_info[page].pobs[c1].pob_data), pob_height(main_info.page_info[page].pobs[c1].image, main_info.page_info[page].pobs[c1].pob_data), (unsigned char *)main_info.pob_backbuf[page] + back_buf_ofs);
		if (scale_up)
			back_buf_ofs += pob_width(main_info.page_info[page].pobs[c1].image, main_info.page_info[page].pobs[c1].pob_data) * pob_height(main_info.page_info[page].pobs[c1].image, main_info.page_info[page].pobs[c1].pob_data) * 4;
		else
			back_buf_ofs += pob_width(main_info.page_info[page].pobs[c1].image, main_info.page_info[page].pobs[c1].pob_data) * pob_height(main_info.page_info[page].pobs[c1].image, main_info.page_info[page].pobs[c1].pob_data);
		put_pob(page, main_info.page_info[page].pobs[c1].x, main_info.page_info[page].pobs[c1].y, main_info.page_info[page].pobs[c1].image, main_info.page_info[page].pobs[c1].pob_data, 1, mask_pic);
	}

}
