cerfa()
    {
        if (ui->cerfa->currentIndex() == 0)
            return FspPrinter::S12541_01;
        else if (ui->cerfa->currentIndex() == 1)
            return FspPrinter::S12541_02;
        else if (ui->cerfa->currentIndex() == 2)
            return FspPrinter::S12541_02_2;
        return FspPrinter::S12541_01;
    }
