getTreeItemText(QTreeWidgetItem *item, int indent = 0)
    {
        if (!item)
            return QString::null;
        QString text;
        if (item->columnCount() == 2) {
            text = QString("%1%2\n%3\n")
                    .arg(QString().fill(' ', indent))
                    .arg(item->text(0).leftJustified(35, ' '))
                    .arg(Utils::indentString(item->text(1), 10+indent));
        } else {
            text = Utils::indentString(item->text(0), indent) + "\n";
        }
        for(int i=0; i < item->childCount(); ++i)
            text += getTreeItemText(item->child(i), indent + 4);
        return text;
    }
