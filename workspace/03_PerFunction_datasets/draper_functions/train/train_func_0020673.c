ProjectCopyTreeNodeRecursively(wxTreeCtrl* tree, const wxTreeItemId& item, const wxTreeItemId& new_parent)
{

    if (!tree || !item.IsOk() || !new_parent.IsOk())
        return;

    FileTreeData* ftd       = (FileTreeData*)tree->GetItemData(item);
    FileTreeData* ftd_moved = ftd ? new FileTreeData(*ftd) : nullptr;
    int           idx       = tree->GetItemImage(item);
    wxColour      col       = tree->GetItemTextColour(item);

    wxTreeItemId insert = ProjectFindNodeToInsertAfter(tree, tree->GetItemText(item), new_parent, ftd && ftd->GetKind() == FileTreeData::ftdkVirtualFolder);
    wxTreeItemId target = tree->InsertItem(new_parent, insert, tree->GetItemText(item), idx, idx, ftd_moved);
    tree->SetItemTextColour(target, col);


    if (tree->ItemHasChildren(item))
    {

        wxTreeItemIdValue cookie;
        wxTreeItemId child = tree->GetFirstChild(item, cookie);
        while (child.IsOk())
        {
            ProjectCopyTreeNodeRecursively(tree, child, target);
            child = tree->GetNextChild(item, cookie);
        }
    }

    if (!tree->IsExpanded(new_parent))
        tree->Expand(new_parent);

    if (ftd_moved && ftd_moved->GetProjectFile())
        ftd_moved->GetProjectFile()->virtual_path = GetRelativeFolderPath(tree, new_parent);
}
