validateAlert()
{
    QVariant validate = alertCore().execute(_item, AlertScript::OnAboutToValidate);
    if ((validate.isValid() && validate.canConvert(QVariant::Bool) && validate.toBool()) ||
            validate.isNull() || !validate.isValid()) {
        _item.validateAlertWithCurrentUserAndConfirmationDialog();
        if (_autoSave)
            alertCore().saveAlert(_item);
    }
}
