InitGraphics()
{
    QLinearGradient fillgrad(0, 2, 0, 36);
    fillgrad.setColorAt(0.0, QColor("#f7f8fa"));
    fillgrad.setColorAt(0.5, QColor("#b9babc"));
    mFillOutBrush = QBrush(fillgrad);

    QLinearGradient fillovergrad(0, 2, 0, 36);
    fillovergrad.setColorAt(0.0, QColor("#f7f8fa"));
    fillovergrad.setColorAt(1.0, QColor("#b9babc"));
    mFillOverBrush = QBrush(fillovergrad);

    QLinearGradient framegrad(0, 0, 0, 40);
    framegrad.setColorAt(1.0, QColor(0, 0, 0, 0xa0));
    framegrad.setColorAt(0.0, QColor(0xff, 0xff, 0xff, 0xa0));
    mFrameOutBrush = QBrush(framegrad);

    QLinearGradient frameovergrad(0, 0, 0, 40);
    frameovergrad.setColorAt(0.0, QColor(0, 0, 0, 0xa0));
    frameovergrad.setColorAt(1.0, QColor(0xff, 0xff, 0xff, 0xa0));
    mFrameOverBrush = QBrush(frameovergrad);
}
