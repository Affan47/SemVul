toggleSplitted()
{
    int count = _multiView->childCount();
    if (count<1) count = 1;
    if (count>2) count = 2;
    count = 3-count;
    _multiView->setChildCount(count);

    _splittedToggleAction->setChecked(count>1);
    _splitDirectionToggleAction->setEnabled(count>1);
    _splitDirectionToggleAction->setChecked(_multiView->orientation() ==
					    Qt::Horizontal);
}
