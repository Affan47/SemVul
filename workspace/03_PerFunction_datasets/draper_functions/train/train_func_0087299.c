printCheque()
{

    ChequePrinter print;
    print.setDrawRects(DrawRects);
    print.setOrder(ui->order->text());
    print.setPlace(ui->place->text());
    print.setDate(ui->date->date());
    if (!ui->valueLineEdit->text().simplified().isEmpty()) {
        print.setAmount(ui->valueLineEdit->text().toDouble());
    } else if (ui->valueListWidget->selectionModel()->hasSelection()) {
        print.setAmount(ui->valueListWidget->selectionModel()->currentIndex().data().toDouble());
    } else {
        Utils::warningMessageBox(tr("No amount"), tr("Please specify an amount for the cheque."));
        return false;
    }
    if (!print.print(_printFormatModel->chequePrintFormat(ui->chequeFormat->selectionModel()->currentIndex()))) {
        LOG_ERROR("Unable to print cheque");
        return false;
    }
    return true;
}
