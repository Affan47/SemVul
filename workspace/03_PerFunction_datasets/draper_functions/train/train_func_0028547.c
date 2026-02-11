addTab(QWidget * widget, const QString & label, bool front, bool setCurrent)
{

    int idx = m_commonUi->tab->insertTab(front ? 0 : m_commonUi->tab->count(), widget, label);


    if (setCurrent)
        m_commonUi->tab->setCurrentIndex(idx);


    if (m_commonUi->tab->parentWidget())
        m_commonUi->tab->parentWidget()->adjustSize();
}
