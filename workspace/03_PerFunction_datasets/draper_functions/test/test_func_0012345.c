OnSearchCfg(wxCommandEvent& )

{
	wxMenu* searchCfgMenu = new wxMenu();
	wxMenu* searchScopeMenu = new wxMenu();

	searchScopeMenu->AppendRadioItem(idMnuScopeSnippets, _("Snippets"));
	searchScopeMenu->AppendRadioItem(idMnuScopeCategories, _("Categories"));
	searchScopeMenu->AppendRadioItem(idMnuScopeBoth, _("Snippets and categories"));
	switch (GetConfig()->m_SearchConfig.scope)
	{
		case CodeSnippetsConfig::SCOPE_SNIPPETS:
			searchScopeMenu->Check(idMnuScopeSnippets, true);
		break;

		case CodeSnippetsConfig::SCOPE_CATEGORIES:
			searchScopeMenu->Check(idMnuScopeCategories, true);
		break;

		case CodeSnippetsConfig::SCOPE_BOTH:
			searchScopeMenu->Check(idMnuScopeBoth, true);
		break;
	}

	searchCfgMenu->AppendCheckItem(idMnuCaseSensitive, _("Case sensitive"));
	if (GetConfig()->m_SearchConfig.caseSensitive)
	{
		searchCfgMenu->Check(idMnuCaseSensitive, true);
	}

	searchCfgMenu->Append(idMnuScope, _("Scope"), searchScopeMenu);
	searchCfgMenu->AppendSeparator();
	searchCfgMenu->Append(idMnuClear, _("Clear"));
    searchCfgMenu->Append(idMnuSearchExtended, _("Full Search"));
    searchCfgMenu->Append(idMnuSettings, _("Settings..."));

	if (m_SearchSnippetCtrl->GetValue().IsEmpty())
	{
		searchCfgMenu->Enable(idMnuClear, false);
	}


	wxRect btnRect = m_SearchCfgBtn->GetRect();
	PopupMenu(searchCfgMenu, btnRect.x + btnRect.GetWidth(), btnRect.y);

	searchCfgMenu->Destroy(idMnuScope);
	delete searchCfgMenu;
}
