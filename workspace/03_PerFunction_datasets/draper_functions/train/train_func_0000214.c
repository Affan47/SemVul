standingOrdersClicked() {
    m_shipCountEdit->setFocus();
    if(m_standingOrder->checkState() == Qt::Checked)
        m_shipValidator->setTop(INT_MAX);
    else
        m_shipValidator->setTop(sourcePlanet->fleet().shipCount());
}
