setPageSize(const char* name)
{
    PageSizeInfo* info = PageSizeInfo::getPageSizeByName(name);
    if (info) {
	setPageWidth(info->width() / 25.4);
	setPageHeight(info->height() / 25.4);
	delete info;
	return (true);
    } else
	return (false);
}
