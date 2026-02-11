getPrescriptionData(const IDrug *drug, const int column) const
    {
        using namespace ::DrugsDB::Constants;
        Q_ASSERT(drug);
        if (!drug)
            return QVariant();
        if (column ==  Prescription::ToHtml) {
            return q->getFullPrescription(drug, true);
        } else {
            return drug->prescriptionValue(column);
        }
        return QVariant();
    }
