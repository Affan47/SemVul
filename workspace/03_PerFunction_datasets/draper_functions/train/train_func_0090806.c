updateSnapShot()
{


    contentSnapShot = QPixmap(content->size());
    contentSnapShot.fill(Qt::transparent);
    content->render(&contentSnapShot, QPoint(), QRegion(), QWidget::DrawChildren);
}
