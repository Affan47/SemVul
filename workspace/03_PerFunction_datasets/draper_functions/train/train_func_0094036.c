unitsOfLength()
{
    static QHash<UnitsOfLength, QPair<QString, double> > units;
    if (units.empty()) {
        static const struct
        {
            Types::UnitsOfLength unit;
            QString name;
            double cm;
        } unitsOfLength[] = {
            {Types::UnitOfLengthMeter,      QLatin1String("m"),        100.00},
            {Types::UnitOfLengthMillimeter, QLatin1String("mm"),         0.10},
            {Types::UnitOfLengthCentimeter, QLatin1String("cm"),         1.00},
            {Types::UnitOfLengthInch,       QLatin1String("in"),         2.54},
            {Types::UnitOfLengthFeet,       QLatin1String("ft"), 2.54 * 12.00},
            {Types::UnitOfLengthPoints,     QLatin1String("pt"), 2.54 / 72.00}
        };
        static const int unitsOfLengthCount = sizeof(unitsOfLength)/sizeof(unitsOfLength[0]);
        for (int i = 0; i < unitsOfLengthCount; i++)
            units.insert(unitsOfLength[i].unit, QPair<QString, double> (unitsOfLength[i].name, unitsOfLength[i].cm));
    }
    return units;
}
