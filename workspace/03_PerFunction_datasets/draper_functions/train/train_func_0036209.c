amountPrintingValue(const Fsp &fsp, FspPrinter::Cerfa cerfa, int line, int fspIndex)
    {
        Q_UNUSED(cerfa);
        if (fsp.amountLineData(line, fspIndex).isNull())
            return QString::null;
        switch (fspIndex) {
        case Fsp::Amount_Date:
            return fsp.amountLineData(line, fspIndex).toDate().toString("ddMMyyyy");
        case Fsp::Amount_ActCode:
            return fsp.amountLineData(line, fspIndex).toString().left(7);
        case Fsp::Amount_Activity:
            return fsp.amountLineData(line, fspIndex).toString().left(1);
        case Fsp::Amount_CV:
        case Fsp::Amount_OtherAct1:
        case Fsp::Amount_OtherAct2:
            return fsp.amountLineData(line, fspIndex).toString().left(5);
        case Fsp::Amount_Depassement:
        case Fsp::Amount_Deplacement_IKMD:
            return fsp.amountLineData(line, fspIndex).toString().left(2);
        case Fsp::Amount_Deplacement_Nb:
            return fsp.amountLineData(line, fspIndex).toString().left(2).rightJustified(2, '*');
        case Fsp::Amount_Amount:
            return QString::number(fsp.amountLineData(line, fspIndex).toDouble(), 'f', 2).remove(".").rightJustified(6, '*');
        case Fsp::Amount_Deplacement_IKValue:
            return QString::number(fsp.amountLineData(line, fspIndex).toDouble(), 'f', 2).remove(".").rightJustified(4, '*');
        }
        return QString::null;
    }
