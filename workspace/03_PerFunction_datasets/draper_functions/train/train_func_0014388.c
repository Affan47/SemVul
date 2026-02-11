UpdateSharedDirectories()
{

	if (m_IsRemote) {
		DeleteChildren(m_root);


#if 0
		for (SharedMap::iterator it = m_lstShared.begin(); it != m_lstShared.end(); it++) {
#else
		for (SharedMap::iterator it = m_lstShared.begin(); it != m_lstShared.end(); ++it) {
#endif

			AppendItem(m_root, it->second.GetPrintable(), IMAGE_FOLDER, -1, new CItemData(it->second));
		}
		return;
	}


	wxTreeItemIdValue cookie;
	wxTreeItemId hChild = GetFirstChild(GetRootItem(), cookie);

	while (hChild.IsOk()) {

		if (HasSharedSubdirectory(GetFullPath(hChild))) {
			SetHasSharedSubdirectory(hChild, true);
		}


		if (IsShared(GetFullPath(hChild))) {
			SetItemBold(hChild, true);
		}

		hChild = GetNextSibling(hChild);
	}
}
