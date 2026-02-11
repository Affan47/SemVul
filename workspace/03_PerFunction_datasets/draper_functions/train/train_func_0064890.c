OnBeginLabelEdit(wxTreeEvent& event)

{

	if (event.GetItem() == GetSnippetsTreeCtrl()->GetRootItem())
	{
		event.Veto();
	}
	IsEditingLabel(true);
}
