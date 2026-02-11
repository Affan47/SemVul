findLabel(Form::FormItem *item)
{
    QLabel *l = 0;

    const QString &lbl = item->spec()->value(Form::FormItemSpec::Spec_UiLabel).toString();
    if (!lbl.isEmpty()) {
        l = item->parentFormMain()->formWidget()->findChild<QLabel*>(lbl);
        if (l) {
            l->setText(item->spec()->label());
        } else {
            LOG_ERROR_FOR("TextEditorFactory", "Label not found");
            l = new QLabel(item->formWidget());
            l->setText(item->spec()->label());
        }
    }
    return l;
}
