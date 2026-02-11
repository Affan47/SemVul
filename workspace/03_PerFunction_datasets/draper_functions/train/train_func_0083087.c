_deleteFollowingIfAtInsPoint() const
{

	FV_View* pView = _getView();
    if(!pView || !pView->getShowPara())
    {
    	return true;
    }

	return false;
}
