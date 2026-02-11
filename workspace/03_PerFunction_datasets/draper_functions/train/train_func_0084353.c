_k_size_chosen_slot(const QString& size)
{
    if ( !signalsAllowed ) {
        return;
    }

    signalsAllowed = false;

    qreal currentSize;
    if (size.isEmpty()) {
        currentSize = KGlobal::locale()->readNumber(sizeListBox->currentItem()->text());
    } else {
        currentSize = KGlobal::locale()->readNumber(size);
    }


    if (customSizeRow >= 0 && selFont.pointSizeF() != currentSize) {
        sizeListBox->item(customSizeRow)->setText(standardSizeAtCustom);
        customSizeRow = -1;
    }

    sizeOfFont->setValue(currentSize);
    selFont.setPointSizeF(currentSize);
    emit q->fontSelected(selFont);

    if (!size.isEmpty()) {
        selectedSize = currentSize;
    }

    signalsAllowed = true;
}
