on_userformsButton_clicked()
{
    if (settings()->value(S_USERRECORDEDFORMS, QVariant()).isNull())
        return;

    const QStringList &ulist = settings()->value(S_USERRECORDEDFORMS).toStringList();
    QList<QAction*> list;
    foreach(const QString &form, ulist) {
        if (!form.isEmpty())
            list << new QAction(form, this);
    }
    QAction *aclear = new QAction(tr("Clear this list", "Clear the user's intakes recorded forms"), this);
    list << aclear;

    QAction *a = QMenu::exec(list, userformsButton->mapToGlobal(QPoint(0,20)));
    if (!a)
        return;
    if (a == aclear) {
        settings()->setValue(S_USERRECORDEDFORMS, QString());
    } else {
        intakesCombo->setEditText(a->text());
        if (d->m_DosageModel)
            d->m_DosageModel->setData(d->m_DosageModel->index(d->m_Mapper->currentIndex(),Dosages::Constants::IntakesScheme),a->text());
        else
            drugModel()->setDrugData(d->m_DrugId, DrugsDB::Constants::Prescription::IntakesScheme, a->text());
    }
}
