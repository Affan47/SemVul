set(const Jid &jid, const QString &prompt)
{
	type = 1;
	v_jid = jid;
	v_prompt = prompt;
	iq = createIQ(doc(), "set", v_jid.full(), id());
	QDomElement query = doc()->createElement("query");
	query.setAttribute("xmlns", "jabber:iq:gateway");
	iq.appendChild(query);
	query.appendChild(textTag(doc(), "prompt", v_prompt));
}
