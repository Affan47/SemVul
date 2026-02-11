UpdateParentItems(wxTreeItemId hChild, bool add)
{
	wxTreeItemId parent = hChild;
	while (parent != GetRootItem()) {
		parent = GetItemParent(parent);
		if (add) {
			if (GetItemImage(parent) == IMAGE_FOLDER_SUB_SHARED) {

				break;
			} else {
				SetHasSharedSubdirectory(parent, true);
			}
		} else {
			if (GetItemImage(parent) == IMAGE_FOLDER_SUB_SHARED) {

				if (HasSharedSubdirectory(GetFullPath(parent))) {

					break;
				} else {

					SetHasSharedSubdirectory(parent, false);
				}
			} else {
				break;
			}
		}
	}
}
