makeLocalModifications(QByteArray & svg, const QString & filename) {


    switch (m_viewID) {
        case ViewLayer::PCBView:
            return false;

        default:
            if (itemType() != ModelPart::Part) return false;
            if (filename.startsWith("icon")) return false;

            break;
    }

    bool gotChipLabel = false;
    QString chipLabel = modelPart()->properties().value("chip label", "");
    if (!chipLabel.isEmpty()) {
        svg = TextUtils::replaceTextElement(svg, "label", chipLabel);
        gotChipLabel = true;
    }

    bool modified = false;
    if (m_viewID == ViewLayer::SchematicView) {
        QString value = modelPart()->properties().value("editable pin labels", "");
        if (value.compare("true") == 0) {
            bool hasLayout, sip;
            QStringList labels = sipOrDipOrLabels(hasLayout, sip);
            if (labels.count() > 0) {
                svg = PartFactory::makeSchematicSipOrDipOr(labels, hasLayout, sip).toUtf8();
                modified = true;
            }
        }
        gotChipLabel = true;
    }

    if (gotChipLabel) return modified;

    int rix = svg.indexOf("label");
    if (rix >= 0) {
        rix = qMax(0, rix - 4);
        int ix = svg.indexOf("id=\"label\"", rix);
        if (ix < 0) {
            ix = svg.indexOf("id='label'", rix);
        }
        if (ix >= 0) {
            int tix = svg.lastIndexOf("<text", ix);
            int lix = svg.lastIndexOf("<", ix);
            if (tix == lix) {
                svg = TextUtils::replaceTextElement(svg, "label", modelPart()->title());
                modified = true;
            }
        }
    }

    return modified;
}
