setData(const QModelIndex &index, const QVariant &value, int role)
{
    Q_ASSERT_X(!m_UID.isNull(), "DosageModel::setData", "before using the dosagemodel, you must specify the UID of the related drug");
    if (!index.isValid())
        return false;

    if (role == Qt::EditRole || role == Qt::DisplayRole) {
        QVariant q = data(index);


        if (index.column() != Dosages::Constants::ModificationDate)
            setData(this->index(index.row(), Dosages::Constants::ModificationDate), QDateTime::currentDateTime());


        if (!m_DirtyRows.contains(index.row())) {
            m_DirtyRows << index.row();
        }


        if (index.column()==Dosages::Constants::Refill) {
            _refills.insert(index.row(), value.toInt());
        } else if (index.column()==Dosages::Constants::Route) {
            m_Route = value.toString();

            IDrug *drug = m_DrugsModel->getDrug(m_UID);
            int routeId = -1;
            for(int i = 0; i < drug->drugRoutes().count(); ++i) {
                if (drug->drugRoutes().at(i)->label()==value.toString()) {
                    routeId = drug->drugRoutes().at(i)->routeId();
                    break;
                }
            }

            if (routeId != -1) {
                if (!QSqlTableModel::setData(QSqlTableModel::index(index.row(), Dosages::Constants::RouteId), routeId, role)) {
                    LOG_ERROR("Can not set data to QSqlTableModel");
                    LOG_QUERY_ERROR(query());
                    return false;
                }
            } else {
                LOG_ERROR("Route not found: " + value.toString());
            }
            Q_EMIT dataChanged(index, index);
            return true;
        } else {
            if (!QSqlTableModel::setData(index, value, role)) {
                LOG_ERROR("Can not set data to QSqlTableModel");
                LOG_QUERY_ERROR(query());
                return false;
            }
        }
        Q_EMIT dataChanged(index, index);

        QModelIndex label = this->index(index.row(), Dosages::Constants::Label);
        Q_EMIT dataChanged(label, label);
    }
    return false;
}
