on_butIAMSend_clicked()
{
    if (drugModel()->drugsList().isEmpty())
        return;


    QString msg;
    msg = tr("Testing: ") + "\n";
    foreach(DrugsDB::IDrug * drug, drugModel()->drugsList())
        msg += drug->brandName() + "\n";


    if (chkAllInteractionsFound->isChecked()) {
        msg += tr("All interactions found.\n");
    } else {
        msg += tr("*** Missing interactions.\n");
    }

    if (chkAllInteractionsOK->isChecked())  {
        msg += tr("All interactions are OK.\n");
    } else {
        msg += tr("*** Wrong interactions.\n");
    }

    if (chkAllIAMTextsOK->isChecked()) {
        msg += tr("IAM Text is correct.\n");
    } else {
        msg += tr("*** IAM Text is incorrect.\n");
    }

    if (chkAllCATTextsOK->isChecked()) {
        msg += tr("CAT Text is correct.\n");
    } else {
        msg += tr("*** CAT Text is incorrect.\n");
    }

    msg += tr("Message: ") + InteractMessage->toPlainText() + "\n";

    if ((chkAllInteractionsFound->isChecked()) &&
        (chkAllInteractionsOK->isChecked()) &&
        (chkAllIAMTextsOK->isChecked()) &&
        (chkAllCATTextsOK->isChecked())) {
        msg += "\n" + tr("Checked interactions: ") + "\n";
        foreach(DrugsDB::IDrug *drug, drugModel()->drugsList()) {
            Q_UNUSED(drug);
            foreach(QVariant code, drugModel()->drugData(m_DrugUid,DrugsDB::Constants::Drug::CodeMoleculesList).toList())
                msg +=  code.toString() + "\n";
        }
    }

    m_Sender.setParent(m_Parent);
    m_Sender.setUser("eric");
    m_Sender.setMessage(msg);
    m_Sender.postMessage();
    m_InteractSent = true;
}
