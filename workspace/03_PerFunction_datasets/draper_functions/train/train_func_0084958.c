addCurrentPatientAlerts()
{
    QString u;
    if (patient()) {
        u = patient()->uuid();
    } else {
        if (!Utils::isReleaseCompilation())
            u = "patient1";
    }
    if (!_patientUids.contains(u))
        _patientUids << u;
}
