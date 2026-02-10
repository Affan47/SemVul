expandDim(const QSize& orig, WidgetType wt, int baseMarginMetric,
                        const QStyleOption* opt, const QWidget* w, bool rotated) const
{
    int addWidth =  2*widgetLayoutProp(wt, baseMarginMetric + MainMargin, opt, w) +
                    widgetLayoutProp(wt, baseMarginMetric + Left, opt, w) +
                    widgetLayoutProp(wt, baseMarginMetric + Right, opt, w);

    int addHeight = 2*widgetLayoutProp(wt, baseMarginMetric + MainMargin, opt, w) +
                    widgetLayoutProp(wt, baseMarginMetric + Top, opt, w) +
                    widgetLayoutProp(wt, baseMarginMetric + Bot, opt, w);

    return QSize(orig.width() + (rotated? addHeight: addWidth),
                 orig.height() + (rotated? addWidth: addHeight));
}
