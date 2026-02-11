get_image_page(gfp_t gfp_mask, int safe_needed)
{
	void *res;

	res = (void *)get_zeroed_page(gfp_mask);
	if (safe_needed)
		while (res && swsusp_page_is_free(virt_to_page(res))) {

			swsusp_set_page_forbidden(virt_to_page(res));
			allocated_unsafe_pages++;
			res = (void *)get_zeroed_page(gfp_mask);
		}
	if (res) {
		swsusp_set_page_forbidden(virt_to_page(res));
		swsusp_set_page_free(virt_to_page(res));
	}
	return res;
}
