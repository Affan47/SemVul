showDetails(QListWidgetItem *item)
{
    if (item) {
        PluginSpec *spec = item->data(Qt::UserRole).value<PluginSpec *>();
        m_ui->pluginError->setText(spec->errorString());
    } else {
        m_ui->pluginError->setText(QString());
    }
}
