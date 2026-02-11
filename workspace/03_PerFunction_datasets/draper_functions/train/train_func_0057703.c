registerVal (const QString &key,
								const QString &help,
								const PreferenceValue::ValueType &type,
								const QVariant &defval,
								const QVariant &data,
								const PreferenceValue::ValueSection &section)
{
	PreferenceValue *val = new PreferenceValue (key, help, type, defval, data, section);
	m_values[key] = val;
	m_sections[section] = val;

	QSettings s;
	if (!s.contains (key)) {
		qDebug ("creating config value %s", qPrintable (key));
		s.setValue (key, defval);
	}
}
