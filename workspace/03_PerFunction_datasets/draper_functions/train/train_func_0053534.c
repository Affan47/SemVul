get_sort_category (NautilusFile *file)
{
	NautilusDesktopLink *link;
	SortCategory category;

	category = SORT_OTHER;

	if (NAUTILUS_IS_DESKTOP_ICON_FILE (file)) {
		link = nautilus_desktop_icon_file_get_link (NAUTILUS_DESKTOP_ICON_FILE (file));
		if (link != NULL) {
			switch (nautilus_desktop_link_get_link_type (link)) {
			case NAUTILUS_DESKTOP_LINK_HOME:
				category = SORT_HOME_LINK;
				break;
			case NAUTILUS_DESKTOP_LINK_MOUNT:
				category = SORT_MOUNT_LINK;
				break;
			case NAUTILUS_DESKTOP_LINK_TRASH:
				category = SORT_TRASH_LINK;
				break;
			case NAUTILUS_DESKTOP_LINK_NETWORK:
				category = SORT_NETWORK_LINK;
				break;
			default:
				category = SORT_OTHER;
				break;
			}
			g_object_unref (link);
		}
	}

	return category;
}
