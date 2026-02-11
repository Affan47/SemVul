ipro_del(GF_Box *s)
{
	u32 count, i;
	GF_ItemProtectionBox *ptr = (GF_ItemProtectionBox *)s;
	if (ptr == NULL) return;
	count = gf_list_count(ptr->protection_information);
	for (i = 0; i < count; i++) {
		GF_Box *a = (GF_Box *)gf_list_get(ptr->protection_information, i);
		gf_isom_box_del(a);
	}
	gf_list_del(ptr->protection_information);
	gf_free(ptr);
}
