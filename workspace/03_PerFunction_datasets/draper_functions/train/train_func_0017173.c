read(QIODevice *device)
{
    colorParams.clear();

    QString errorStr;
    int errorLine;
    int errorColumn;

    if (!domDocument.setContent(device, true, &errorStr, &errorLine,
                                &errorColumn))
    {
        if(showMessages)
        {
            QMessageBox::information(window(), tr("Color File Parser"),
                                 tr("Parse error at line %1, column %2:\n%3")
                                 .arg(errorLine)
                                 .arg(errorColumn)
                                 .arg(errorStr));
        }
        return false;
    }

    QDomElement root = domDocument.documentElement();
    if (root.tagName() != "colorparam")
    {
        if(showMessages)
        {
            QMessageBox::information(window(), tr("Color File"),
                                 tr("The file is not a color parameter file."));
        }
        return false;
    }

    int numColors = 0;
    QDomElement rgbIndex = root.firstChildElement("rgbindex");
    if (!rgbIndex.isNull())
    {
        numColors = parseRGBIndex(rgbIndex);
    }
    if(numColors == 0)
    {

        colorParams.useHardCodedColors();
    }

    QDomElement consensus = root.firstChildElement("consensus");
    if (!consensus.isNull())
    {
        parseConsensus(consensus);
    }

    QDomElement colorRules = root.firstChildElement("colorrules");
    int numOfRules = 0;
    if (!colorRules.isNull())
    {
        numOfRules = parseColorRule(colorRules);
    }
    if(numOfRules == 0)
    {

        if(showMessages)
        {


        }
        colorParams.useDefaultColorRules();
    }

    return true;
}
