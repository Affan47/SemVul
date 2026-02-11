text(QPainter *p, int index)
    {
        QString elementID = QString("label%1").arg(index);
        QString text = labels[index];

        if (image->hasElement(elementID)) {
            QRectF elementRect = image->elementRect(elementID);
            Qt::Alignment align = Qt::AlignCenter;


            if (colors.count() > index) {
                p->setPen(QPen(colors[index]));
            } else {
                p->setPen(Plasma::Theme::defaultTheme()->color(Plasma::Theme::TextColor));
            }
            if (fonts.count() > index) {
                p->setFont(fonts[index]);
            }

            QFontMetricsF fm(p->font());

            if (elementRect.height() < fm.height()) {
                QPointF oldCenter = elementRect.center();
                elementRect.setHeight(fm.height());
                elementRect.moveCenter(oldCenter);
            }

            if (alignments.count() > index) {
                align = alignments[index];
            }
            if (elementRect.width() > elementRect.height()) {
                if (align&Qt::AlignLeft) {
                    p->drawText(elementRect.bottomLeft(), text);
                } else {
                    p->drawText(elementRect, align, text);
                }
            } else {
                p->save();
                QPointF rotateCenter(
                        elementRect.left() + elementRect.width() / 2,
                        elementRect.top() + elementRect.height() / 2);
                p->translate(rotateCenter);
                p->rotate(-90);
                p->translate(elementRect.height() / -2,
                             elementRect.width() / -2);
                QRectF r(0, 0, elementRect.height(), elementRect.width());
                p->drawText(r, align, text);
                p->restore();
            }
        }
    }
