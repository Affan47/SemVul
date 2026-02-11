executeXmlUpdate(QString &xml) const
    {

        xml.replace("<FullPrescription version=\"0.6.0\">", "<FullPrescription version=\"0.7.2\">");
        return true;
    }
