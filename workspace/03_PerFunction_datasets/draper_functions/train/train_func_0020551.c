createItemWidget(Form::FormItem *item, QWidget *parent)
{
    if (!item)
        return false;


    QString requestedWidgetName = item->spec()->pluginName().toLower();
    Form::IFormWidgetFactory *factory = m_PlugsFactories.value(requestedWidgetName);
    Form::IFormWidget *w = 0;


    if (requestedWidgetName.isEmpty()) {
        LOG_ERROR_FOR("XmlFormContentReader", "No plugin name for item: " + item->uuid());
        factory = m_PlugsFactories.value("helptext");
        w = factory->createWidget("helptext", item);
        item->spec()->setValue(Form::FormItemSpec::Spec_Label, QString("XML FORM ERROR: Requested widget does not exist for item '%1'").arg(item->uuid()));
        return false;
    }


    if (!factory) {
        LOG_ERROR_FOR("XmlFormContentReader", QString("Form error in item '%1': Requested widget '%2' does not exist in plugin's widgets list.").arg(item->uuid()).arg(requestedWidgetName));

        factory = m_PlugsFactories.value("helptext");
        item->spec()->setValue(Form::FormItemSpec::Spec_Label, QString("XML FORM ERROR: Requested widget does not exist for item '%1'").arg(item->uuid()));
        w = factory->createWidget("helptext", item);
        return false;
    }


    w = factory->createWidget(requestedWidgetName, item, parent);
    if (w->isContainer()) {
        foreach(Form::FormItem *child, item->formItemChildren()) {


            createItemWidget(child, w);
        }
    }


    Form::IFormWidget *p = qobject_cast<Form::IFormWidget*>(parent);
    if (p)
        p->addWidgetToContainer(w);
    return true;
}
