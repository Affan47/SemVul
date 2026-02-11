layoutTextItems(const QStyleOptionViewItemV4 &option, const QModelIndex &index,
                                                 QTextLayout *labelLayout, QTextLayout *infoLayout,
                                                 QRect *textBoundingRect) const
{
    KFileItem item       = fileItem(index);
    const QString info   = information(option, index, item);
    bool showInformation = false;

    setLayoutOptions(*labelLayout, option);

    const QRect textArea = labelRectangle(option);
    QRect textRect       = subtractMargin(textArea, Private::TextMargin);


    QSize maxLabelSize = textRect.size();
    QSize maxInfoSize  = textRect.size();
    QSize labelSize;
    QSize infoSize;


    if (!info.isEmpty() && textRect.height() >= option.fontMetrics.lineSpacing() * 2)
    {
        infoLayout->setFont(labelLayout->font());
        infoLayout->setTextOption(labelLayout->textOption());

        maxLabelSize.rheight() -= option.fontMetrics.lineSpacing();
        showInformation = true;
    }


    labelSize = layoutText(*labelLayout, option, option.text, maxLabelSize);
    maxInfoSize.rheight() -= labelSize.height();


    if (showInformation)
        infoSize = layoutText(*infoLayout, option, info, maxInfoSize);
    else
        infoSize = QSize(0, 0);


    const QSize size(qMax(labelSize.width(), infoSize.width()), labelSize.height() + infoSize.height());
    *textBoundingRect = QStyle::alignedRect(option.direction, option.displayAlignment, size, textRect);


    labelLayout->setPosition(QPointF(textRect.x(), textBoundingRect->y()));
    infoLayout->setPosition(QPointF(textRect.x(), textBoundingRect->y() + labelSize.height()));
}
