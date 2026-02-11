getDouble( const QString &caption, const QString &label,
                  double value, double minValue, double maxValue, double step, int decimals,
                  bool *ok, QWidget *parent )
{
    KInputDialogHelper dlg(caption, label, value, minValue, maxValue, step, decimals, parent);

    bool _ok = (dlg.exec() == KDialog::Accepted);

    if (ok)
        *ok = _ok;

    double result = 0;
    if (_ok)
        result = dlg.doubleSpinBox()->value();

    return result;
}
