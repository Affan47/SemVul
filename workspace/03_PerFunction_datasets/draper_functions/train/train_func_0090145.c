updateObjectProperties(KJS::ExecState* exec, KJS::JSValue* val,
                                                QTreeWidgetItem* item, bool globalObject)
{
    bool root = (item == m_view->invisibleRootItem());


    bool recurse = item->isExpanded() || root;

    QStringList props;
    KJS::JSObject* obj = 0;


    if (val)
    {
        assert (val->isObject());

        obj = val->getObject();
        KJS::PropertyNameArray jsProps;


        obj->getOwnPropertyNames(exec, jsProps, KJS::PropertyMap::ExcludeDontEnumProperties);

        for (int pos = 0; pos < jsProps.size(); ++pos)
        {


            if (globalObject && !obj->getDirect(jsProps[pos]))
                continue;

            props.append(jsProps[pos].ustring().qstring());
        }
    }


    if (val && !val->getObject()->isActivation())
        props << QLatin1String("__proto__");


    if (root && exec)
        props << QLatin1String("this");


    props.sort();


    while (props.size() < item->childCount())
        delete item->takeChild(item->childCount() - 1);

    while (props.size() > item->childCount())
        item->addChild(new QTreeWidgetItem);


    for (int pos = 0; pos < props.size(); ++pos)
    {
        QString propName = props[pos];
        QTreeWidgetItem* kid = item->child(pos);
        kid->setText(0, propName);

        if (root && propName == "this")
            updateValue(exec, exec->thisValue(), kid, true);
        else
            updateValue(exec, obj->get(exec, KJS::Identifier(KJS::UString(props[pos]))), kid, recurse);
    }
}
