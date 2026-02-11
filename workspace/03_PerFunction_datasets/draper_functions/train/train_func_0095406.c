populateWithCurrentPatientData()
{
    if (patient()->uuid().isEmpty())
        return false;
    d->_data.insert(Patient_FullName, patient()->data(Core::IPatient::FullName));
    d->_data.insert(Patient_FullAddress, patient()->data(Core::IPatient::FullAddress));
    d->_data.insert(Patient_DateOfBirth, patient()->data(Core::IPatient::DateOfBirth));
    QString nss = patient()->data(Core::IPatient::SocialNumber).toString();
    d->_data.insert(Patient_Personal_NSS, nss.left(13));
    if (nss.size() > 13)
        d->_data.insert(Patient_Personal_NSSKey, patient()->data(Core::IPatient::SocialNumber).toString().mid(13));
    d->_data.insert(Patient_Assure_FullName, patient()->data(Core::IPatient::SocialNumberOwnerFullName));
    if (!d->_data.value(Patient_Assure_FullName).toString().isEmpty()) {
        d->_data.insert(Patient_Assure_NSS, nss.left(13));
        if (nss.size() > 13)
            d->_data.insert(Patient_Assure_NSSKey, patient()->data(Core::IPatient::SocialNumber).toString().mid(13));
    }

    return true;
}
