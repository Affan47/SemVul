selectCurrent()
{
	int x = lbx_proxy->currentItem();
	if(x != -1)
		lbx_proxy->setSelected(x, true);
}
