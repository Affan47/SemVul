f2fs_follow_link(struct dentry *dentry, void **cookie)
{
	const char *link = page_follow_link_light(dentry, cookie);
	if (!IS_ERR(link) && !*link) {

		page_put_link(NULL, *cookie);
		link = ERR_PTR(-ENOENT);
	}
	return link;
}
