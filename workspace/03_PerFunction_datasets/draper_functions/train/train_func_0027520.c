onPrintTestClicked()
{
    const ChequePrintFormat &format = _model->chequePrintFormat(ui->availableFormats->currentIndex());

    ChequePrinter print;
    print.setDrawRects(true);
    print.setOrder(rectToString(format.rectMillimetersFromTopLeft(ChequePrintFormat::PayTo)));
    print.setPlace(rectToString(format.rectMillimetersFromTopLeft(ChequePrintFormat::Place)));
    print.setDate(QDate::currentDate());
    print.setAmount(1000);
    if (!print.print(format)) {
        LOG_ERROR("Unable to print cheque");
        return false;
    }
    return true;
}
