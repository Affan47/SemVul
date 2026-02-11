take(const QDomElement &x)
{
	if(!iqVerify(x, j, id()))
		return false;

	if(x.attribute("type") == "result") {
		bool found;
		QDomElement q = queryTag(x);
		QDomElement tag;
		tag = findSubTag(q, "name", &found);
		if(found)
			v_name = tagContent(tag);
		tag = findSubTag(q, "version", &found);
		if(found)
			v_ver = tagContent(tag);
		tag = findSubTag(q, "os", &found);
		if(found)
			v_os = tagContent(tag);

		setSuccess();
	}
	else {
		setError(x);
	}

	return true;
}
