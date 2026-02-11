savePmhxCategories(const XmlFormName &form, const QString &content)
{
    Q_UNUSED(form);


    qApp->processEvents(QEventLoop::ExcludeUserInputEvents);
    if (content.isEmpty()) {
        LOG_ERROR("Empty content.");
        return false;
    }

    QDomDocument doc;
    int line = -1;
    int col = -1;
    QString error;
    if (!doc.setContent(content, &error, &line, &col)) {
        LOG_ERROR(QString("Error while loading PMHxCategories XML files.\n  %1: %2;%3").arg(error).arg(line).arg(col));
        return false;
    }
    QDomElement root = doc.firstChildElement(Constants::TAG_MAINXMLTAG);
    QDomElement element = root.firstChildElement(Constants::TAG_PMHX_CATEGORIES);
    element = element.firstChildElement(::Constants::TAG_CATEGORY);
    QVector<Category::CategoryItem *> rootCategories;
    while (!element.isNull()) {
        rootCategories << createCategory(form, element, 0);
        element = element.nextSiblingElement(::Constants::TAG_CATEGORY);
    }


    qApp->processEvents(QEventLoop::ExcludeUserInputEvents);
    if (!categoryCore()->saveCategories(rootCategories)) {
        LOG_ERROR(tr("Error while saving PMHxCateogries (%1)").arg(form.uid));
        return false;
    }

    return true;
}
