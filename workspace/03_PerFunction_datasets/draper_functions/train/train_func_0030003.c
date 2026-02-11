ProjectCanDragNode(cbProject* project, wxTreeCtrl* tree, wxTreeItemId node)
{

    if (!node.IsOk())
        return false;


    FileTreeData* ftd = (FileTreeData*)tree->GetItemData(node);
    if (!ftd)
        return false;


    if (ftd->GetProject() != project)
        return false;


    return (   (ftd->GetKind() == FileTreeData::ftdkFile)
            || (ftd->GetKind() == FileTreeData::ftdkVirtualFolder) );
}
