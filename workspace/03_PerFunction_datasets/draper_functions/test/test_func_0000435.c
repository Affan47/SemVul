xmlVersion(const QString &xml)
    {

        QString v;
        if (xml.startsWith("<?xml version=\"1.0\"") ||
            xml.startsWith("<?xml version='1.0'")) {
            int begin = xml.indexOf("<FullPrescription version=\"") + 27;
            int end = xml.indexOf("\">", begin);
            if (end==-1)
                end = xml.indexOf("\"/>", begin);
            v = xml.mid(begin,end-begin).simplified();
        } else {
            int begin = 15;
            int end = xml.indexOf("\"", begin);
            v = xml.mid(begin,end-begin).simplified();
        }
        return v;
    }
