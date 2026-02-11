currentGender() const
{
    int genderIndex = -1;
    genderIndex = d->ui->genderCombo->currentIndex();

    if (IN_RANGE_STRICT_MAX(genderIndex, 0, Trans::ConstantTranslations::genders().count()))
        return Trans::ConstantTranslations::genders()[genderIndex];

    return QString();
}
