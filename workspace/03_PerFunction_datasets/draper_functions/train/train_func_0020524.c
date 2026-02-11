OnDown(GtkWidget* btn UNUSED, CEditFavDlg* _this)
{
	int sel = _this->m_List->GetCurSel();
	if( sel != -1 && (sel+1) < _this->m_List->Count() )
	{
		_this->m_List->MoveDown(sel);
		CSite tmp = _this->m_Sites[sel];
		_this->m_Sites[sel] = _this->m_Sites[sel+1];
		_this->m_Sites[sel+1] = tmp;
	}
}
