createNewPatient()
{

    Patients::PatientCreatorWizard wiz(this);
    wiz.exec();
    return true;
}
