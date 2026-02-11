click()
{
    QMouseEvent me(QEvent::MouseButtonRelease, QPoint(0,0), Qt::LeftButton, Qt::LeftButton, 0);
    dispatchMouseEvent(&me,0, 1);
    dispatchMouseEvent(&me,EventImpl::CLICK_EVENT, 1);
}
