patientUuid(const QModelIndex &index) const
{
    QModelIndex idx = this->index(index.row(), Core::IPatient::Uid);
    return data(idx).toString();
}
