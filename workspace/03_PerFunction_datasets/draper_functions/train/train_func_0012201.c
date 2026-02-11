cf_packfile_sort_func(const void *elem1, const void *elem2)
{
	cf_root_sort *r1, *r2;
	r1 = (cf_root_sort*)elem1;
	r2 = (cf_root_sort*)elem2;


	if(r1->cf_type == r2->cf_type){
		return stricmp(r1->path, r2->path);
	}


	return (r1->cf_type < r2->cf_type) ? -1 : 1;
}
