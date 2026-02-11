InitTree()
{
#ifndef CLIENT_GUI
	wxTreeItemId root =
#endif
		stattree->AddRoot(theStats::GetTreeRoot()->GetDisplayString());

	ShowStatistics(true);

#ifndef CLIENT_GUI

	stattree->Expand(root);


	wxTreeItemIdValue cookie;
	wxTreeItemId expand_it = stattree->GetFirstChild(root,cookie);

	while(expand_it.IsOk()) {
		stattree->Expand(expand_it);

		expand_it = stattree->GetNextSibling(expand_it);
	}
#endif
}
