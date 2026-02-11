nodeChildren(const QString& node, bool direct, bool internal_nodes) const
{
	QStringList children;
	QString key = node;
	if (!node.isEmpty()) {

		QString subnode;
		if (node.contains('.')) {
			key = node.left(node.indexOf("."));
			subnode = node.right(node.length() - node.indexOf(".") - 1);
		}
		if (trees_.contains(key)) {
			children = trees_[key]->nodeChildren(subnode,direct,internal_nodes);
		}
	}
	else {

		foreach (QString subnode, trees_.keys()) {
			if (internal_nodes)
				children << subnode;

			if (!direct)
				children += nodeChildren(subnode,direct,internal_nodes);
		}

		foreach (QString child, values_.keys()) {
			children << child;
		}
	}

	if (key.isEmpty()) {
		return children;
	}
	else {
		QStringList long_children;
		foreach (QString child, children) {
			QString long_child = QString("%1.%2").arg(key).arg(child);
			long_children << long_child;
		}
		return long_children;
	}
}
