onWidgetClosed(PlexyDesk::AbstractDesktopWidget *)
{
    d->mPostDialog = new FacebookMessageDialog(QRect(boundingRect().x(), boundingRect().y(), boundingRect().width(), 200));
    d->mPostDialog->hide();
    connect(d->mPostDialog, SIGNAL(messageRequested()), this, SLOT(onMessageRestested()));
    connect(d->mPostDialog, SIGNAL(closed(PlexyDesk::AbstractDesktopWidget*)), this, SLOT(onWidgetClosed(PlexyDesk::AbstractDesktopWidget*)));
}
