qle_textChanged(const QString &s)
{
	int x = lbx_proxy->currentItem();
	if(x != -1) {
		unhookEdit();
		lbx_proxy->changeItem(s, x);
		hookEdit();
	}
}
