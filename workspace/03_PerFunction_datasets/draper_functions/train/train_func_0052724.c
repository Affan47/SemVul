updateData( int totalNbLine )
{
    LOG(logDEBUG) << "OverviewWidget::updateData " << totalNbLine;

    linesInFile_ = totalNbLine;
    dirty_ = true;
}
