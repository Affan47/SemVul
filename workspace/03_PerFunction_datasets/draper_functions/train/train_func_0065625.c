movePressedHandle()
{
    switch (lastPressed)
    {
        case QxtSpanSlider::LowerHandle:
            if (lowerPos != lower)
            {
                bool main = (mainControl == QxtSpanSlider::LowerHandle);
                triggerAction(QAbstractSlider::SliderMove, main);
            }
            break;
        case QxtSpanSlider::UpperHandle:
            if (upperPos != upper)
            {
                bool main = (mainControl == QxtSpanSlider::UpperHandle);
                triggerAction(QAbstractSlider::SliderMove, main);
            }
            break;
        default:
            break;
    }
}
