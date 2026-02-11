startElement( const QString&, const QString&,
			 const QString& qName,
			 const QXmlAttributes& qAttributes)
{
    buf.clear();

    if (qName == "Qollector") {
      version = qAttributes.value("version");


      seconds_from_start = 0.0;
      initial_seconds = -1;

      return TRUE;
    }

#define CheckQuarqXml(name,unit,dest)  do { 				\
      if (qName== #name) {						\
	QString name = qAttributes.value( #unit );			\
	QString timestamp = qAttributes.value("timestamp");		\
									\
	if ((! name.isEmpty()) && (!timestamp.isEmpty()) &&		\
	    ( name.toLower() != "nan")) {				\
	  dest = name.toDouble();					\
	  incrementTime(timestamp.toDouble());				\
	}								\
	return TRUE;							\
      }									\
    } while (0);

    CheckQuarqXml(Cadence, RPM, cad );
    CheckQuarqXml(Power, watts, watts );
    CheckQuarqXml(HeartRate, BPM, hr );


    CheckQuarqXml(Speed, RPM, kph );

#undef CheckQuarqXml


    if (!unknown_keys[qName]++)
      std::cerr << "Unknown Element " << qPrintable(qName) << std::endl;
    return TRUE;
}
