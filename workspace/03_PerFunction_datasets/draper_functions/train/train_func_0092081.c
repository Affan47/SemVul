toggleInfo(bool toggle) {
	if(toggle) {
		((QDockWidget*)m_infoView->parent())->show();
	} else {
		((QDockWidget*)m_infoView->parent())->hide();
	}
}
