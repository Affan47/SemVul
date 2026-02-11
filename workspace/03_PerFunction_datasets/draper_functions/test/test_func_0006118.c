scriptlevel(const MmlNode *) const
{
    int parent_sl;
    const MmlNode *p = parent();
    if (p == 0)
	parent_sl = 0;
    else
	parent_sl = p->scriptlevel(this);

    QString expl_sl_str = explicitAttribute("scriptlevel");
    if (expl_sl_str.isNull())
	return parent_sl;

    if (expl_sl_str.startsWith("+") || expl_sl_str.startsWith("-")) {
	bool ok;
	int expl_sl = expl_sl_str.toInt(&ok);
	if (ok) {
	    return parent_sl + expl_sl;
	}
	else {
	    qWarning("MmlNode::scriptlevel(): bad value: %s", qPrintable(expl_sl_str));
	    return parent_sl;
	}
    }

    bool ok;
    int expl_sl = expl_sl_str.toInt(&ok);
    if (ok)
	return expl_sl;


    if (expl_sl_str == "+")
	return parent_sl + 1;
    else if (expl_sl_str == "-")
	return parent_sl - 1;
    else {
	qWarning("MmlNode::scriptlevel(): could not parse value: \"%s\"", qPrintable(expl_sl_str));
	return parent_sl;
    }
}
