setSlowInitialTextParams()
{
    QString num;
    num = num.setNum(clustalw::userParameters->getPWGapOpen());
    slowGapOpen->setText(num);

    num = num.setNum(clustalw::userParameters->getPWGapExtend());
    slowGapExtend->setText(num);
}
