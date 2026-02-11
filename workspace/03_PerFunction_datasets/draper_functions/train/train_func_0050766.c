tweetRide()
{
    QTreeWidgetItem *_item = treeWidget->currentItem();
    if (_item==NULL || _item->type() != RIDE_TYPE) return;

    RideItem *item = dynamic_cast<RideItem*>(_item);

    if (item) {
        TwitterDialog *twitterDialog = new TwitterDialog(this, item);
        twitterDialog->setWindowModality(Qt::ApplicationModal);
        twitterDialog->exec();
    }
}
