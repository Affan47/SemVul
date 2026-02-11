setDrug(const QVariant &drugUid)
{
    using namespace DrugsDB::Constants;
    d->m_DrugUid = drugUid;

    d->drugName->setText(drugModel()->drugData(d->m_DrugUid, Drug::Denomination).toString());
    d->knownMols->addItems(drugModel()->drugData(d->m_DrugUid, Drug::Molecules).toStringList());
    d->DCI->addItems(drugModel()->drugData(d->m_DrugUid, Drug::Inns).toStringList());
    d->interactClass->addItems(drugModel()->drugData(d->m_DrugUid, Drug::InnClasses).toStringList());


    d->m_InteractionsList.clear();
    d->CAT_textBrower->clear();
    d->Info_textBrowser->clear();
    d->listWidgetInteractions->clear();
    QString display;
    if (drugModel()->drugData(d->m_DrugUid, Drug::Interacts).toBool()) {


    }
}
