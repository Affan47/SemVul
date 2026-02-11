slotUpdateBlack(int clickedId)
{
    ui->blackSkill->setEnabled(clickedId == GameStartInformation::AI);
    ui->blackName->setEnabled(clickedId == GameStartInformation::Human);
    if (clickedId == GameStartInformation::Human)
        ui->blackName->setText(m_user.loginName());
    else
        ui->blackName->setText(i18n("Computer"));
}
