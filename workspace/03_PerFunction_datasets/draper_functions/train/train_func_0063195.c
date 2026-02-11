returnHandler()
{
    emit patternConfirmed( editQuickFind_->text(), isIgnoreCase() );

    userRequested_ = false;
    this->hide();
    emit close();
}
