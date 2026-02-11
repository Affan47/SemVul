startBannerPage() const
{
    return (KCupsOptionsPagesWidget::BannerPage) ui.startBannerPageCombo->itemData( ui.startBannerPageCombo->currentIndex() ).toInt();
}
