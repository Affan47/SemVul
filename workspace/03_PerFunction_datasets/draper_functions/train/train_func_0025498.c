toXml(QDomElement & canvasModeElement) const
{
    QDomDocument doc = canvasModeElement.ownerDocument();


    QDomElement modeIdElement = doc.createElement("id");
     canvasModeElement.appendChild(modeIdElement);
     modeIdElement.appendChild(doc.createTextNode(QString::number((int)m_projectMode)));


    if (!m_realSizeInches.isEmpty()) {
        QDomElement modeSizeElement = doc.createElement("size");
         canvasModeElement.appendChild(modeSizeElement);
        QDomElement wElement = doc.createElement("w");
         modeSizeElement.appendChild(wElement);
         wElement.appendChild(doc.createTextNode(QString::number(m_realSizeInches.width())));
        QDomElement hElement = doc.createElement("h");
         modeSizeElement.appendChild(hElement);
         hElement.appendChild(doc.createTextNode(QString::number(m_realSizeInches.height())));
        QDomElement dpiXElement = doc.createElement("dpiX");
         modeSizeElement.appendChild(dpiXElement);
         dpiXElement.appendChild(doc.createTextNode(QString::number(m_canvasDpi.x())));
        QDomElement dpiYElement = doc.createElement("dpiY");
         modeSizeElement.appendChild(dpiYElement);
         dpiYElement.appendChild(doc.createTextNode(QString::number(m_canvasDpi.y())));
    }


    if (m_printDpi != DEFAULT_PRINT_DPI || m_landscape) {
        QDomElement printElement = doc.createElement("print");
         canvasModeElement.appendChild(printElement);
        QDomElement dpiElement = doc.createElement("dpi");
         printElement.appendChild(dpiElement);
         dpiElement.appendChild(doc.createTextNode(QString::number(m_printDpi)));
        QDomElement landscapeElement = doc.createElement("landscape");
         printElement.appendChild(landscapeElement);
         landscapeElement.appendChild(doc.createTextNode(QString::number(m_landscape)));
    }
}
