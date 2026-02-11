slotSearchBegun()
{
    m_ui->listWidget->clear();
    m_ui->listWidget->show();
    if (!m_searchSymbol) {
        m_searchSymbol = new SearchSymbol(m_ui->listWidget->viewport());
        m_searchSymbol->move(2, 2);
        m_searchSymbol->show();
    }
    m_ui->searchButton->setText(tr("Cancel"));
}
