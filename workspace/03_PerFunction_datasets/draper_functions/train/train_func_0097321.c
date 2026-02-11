print(const Internal::ChequePrintFormat &format)
{

    QPrintDialog dlg;
    if (dlg.exec()==QDialog::Rejected)
        return false;
    QPrinter *printer = dlg.printer();
    printer->setFullPage(true);
    printer->setPaperSize(QPrinter::A4);
    printer->setResolution(150);
    printer->setOrientation(QPrinter::Landscape);
    d->_axisHelper.setPageSize(printer->paperRect(), printer->paperSize(QPrinter::Millimeter));


    qreal l, r, t ,b;
    printer->getPageMargins(&l, &t, &r, &b, QPrinter::DevicePixel);
    d->_axisHelper.setMargins(l, t, r, b);


    QPainter painter;
    if (!painter.begin(printer)) {
        qWarning("failed to open file, is it writable?");
        return false;
    }


    double centerX = (printer->paperSize(QPrinter::Millimeter).width() - format.sizeMillimeters().width());
    double centerY = (printer->paperSize(QPrinter::Millimeter).height() / 2.) - (format.sizeMillimeters().height() / 2.);


    centerX -= settings()->value(Core::Constants::S_PRINTERCORRECTION_VERTIC_MM).toDouble();
    centerY -= settings()->value(Core::Constants::S_PRINTERCORRECTION_HORIZ_MM).toDouble();
    d->_axisHelper.translateMillimeters(centerX, centerY);


    QFont font;
    font.setPointSize(10);
    painter.setFont(font);

    painter.save();
    d->drawContent(painter, format);
    painter.restore();
    painter.end();
    return true;
}
