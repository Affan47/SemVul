setModelData(QWidget *editor, QAbstractItemModel *model,
                  const QModelIndex &index) const
{
    LanguageComboBox *combo = qobject_cast<LanguageComboBox*>(editor);
    if (combo) {
        model->setData(index, combo->currentLanguage(), Qt::EditRole);
    }
}
