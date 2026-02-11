buttonPortion(const QRect &totalRect,
                                        const QPoint &pt,
                                        const QStyleOption* opt)
{
   if (opt->state & QStyle::State_Horizontal)
   {

        if (opt->direction == Qt::LeftToRight)
            return pt.x() < totalRect.center().x() ? QStyle::SC_ScrollBarSubLine : QStyle::SC_ScrollBarAddLine;
        else
            return pt.x() > totalRect.center().x() ? QStyle::SC_ScrollBarSubLine : QStyle::SC_ScrollBarAddLine;
    }
    else
    {
        return pt.y() < totalRect.center().y() ? QStyle::SC_ScrollBarSubLine : QStyle::SC_ScrollBarAddLine;
    }
}
