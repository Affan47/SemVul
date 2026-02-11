estimate()
{
    if (byManual->isChecked()) {
        BS->setEnabled(true);
        DP->setEnabled(true);
        TSS->setEnabled(true);
        KJ->setEnabled(true);

        return;
    } else {

        BS->setEnabled(false);
        DP->setEnabled(false);
        TSS->setEnabled(false);
        KJ->setEnabled(false);
    }

    deriveFactors();

    if (byDuration->isChecked()) {

        QTime time = duration->time();
        double hours = (time.hour()) + (time.minute() / 60.00) + (time.second() / 3600.00);

        BS->setValue(hours * timeBS);
        DP->setValue(hours * timeDP);
        TSS->setValue(hours * timeTSS);
        KJ->setValue(hours * timeKJ);

    } else {

        double dist = distance->value();

        BS->setValue(dist * distanceBS);
        DP->setValue(dist * distanceDP);
        TSS->setValue(dist * distanceTSS);
        KJ->setValue(dist * distanceKJ);
    }
}
