about()
{
    QString text, version;
    version = QLatin1String("0.7.4kde");
    text = QString("<h3>QCachegrind %1</h3>").arg(version);
    text += tr("<p>QCachegrind is a graphical user interface for analysing "
	      "profiling data, which helps in the performance optimization "
	      "phase of developing a computer program. "
	      "QCachegrind is open-source, and it is distributed under the "
	      "terms of the GPL v2. For details and source code, see the "
	      "<a href=\"http://kcachegrind.sf.net\">homepage</a> of the "
	      "KCachegrind project.</p>"
              "Main author and maintainer: "
	      "<a href=\"mailto:Josef.Weidendorfer@gmx.de\">"
              "Josef Weidendorfer</a><br>"
              "(with lots of bug fixes and porting to Qt4 by the KDE team)");
    QMessageBox::about(this, tr("About QCachegrind"), text);
}
