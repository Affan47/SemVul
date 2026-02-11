updatePreview()
    {
        FspPrinter printer;
        printer.setDrawRects(false);
        _preview->setPixmap(printer.preview(_fsp, cerfa()).scaledToWidth(700, Qt::SmoothTransformation));
    }
