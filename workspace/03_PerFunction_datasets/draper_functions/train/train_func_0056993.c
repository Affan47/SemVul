on_repeatRadio_toggled(bool checked)
    {
        if (checked) {
            m_ui->dailyTableView->setItemDelegateForColumn(DrugsDB::DailySchemeModel::Value, 0);
            m_ui->dailyTableView->hideColumn(1);
            m_ui->dailyTableView->resizeColumnToContents(0);
            q->model()->setMethod(DrugsDB::DailySchemeModel::Repeat);
        } else {
            q->model()->setMethod(DrugsDB::DailySchemeModel::Distribute);
            m_ui->dailyTableView->showColumn(1);
            m_ui->dailyTableView->resizeColumnToContents(0);
            m_ui->dailyTableView->setItemDelegateForColumn(DrugsDB::DailySchemeModel::Value, m_SpinDelegate);
        }
    }
