getHtmlHeader(const QString &xmlBase64)
    {
        return QString(
                    "<head>\n"
                    "  <meta name=\"qrichtext\" content=\"1\" />\n"
                    "  <meta name=\"charset\" content=\"UTF-8\" />\n"
                    "  <meta name=\"generator\" content=\"%1-%2\" />\n"
                    "  <meta name=\"prescription\" content=\"%3\" />\n"
                    "  <title>%4</title>\n"
                    "  <style type=\"text/css\">\n"
                    "    A:link {text-decoration: none}\n"
                    "    A:visited {text-decoration: none}\n"
                    "    A:active {text-decoration: none}\n"
                    "    A:hover {text-decoration: none;}\n"
                    "  </style>\n"
                    "</head>\n"
                    )
                .arg(qApp->applicationName())
                .arg(qApp->applicationVersion())
                .arg(xmlBase64)
                .arg(QApplication::translate("PrescriptionPrinter", "Pharmaceutical Drugs Prescription"))
                ;
    }
