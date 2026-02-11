SaveTreeState(wxTreeCtrl* tree, const wxTreeItemId& parent, wxArrayString& nodePaths, wxArrayString& selectedItemPaths)
{
    nodePaths.Clear();
    if (!parent.IsOk() || !tree || !tree->ItemHasChildren(parent) || !tree->IsExpanded(parent))
        return;

    wxString tmp;
    if (!DoRememberExpandedNodes(tree, parent, nodePaths, tmp))
        nodePaths.Add(tmp);

    selectedItemPaths.Clear();
    DoRememberSelectedNodes(tree, selectedItemPaths);
}
