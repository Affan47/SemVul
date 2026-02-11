initDatabase(QDir home)
{


    if(dbconn.isOpen()) return;


    db = QSqlDatabase::addDatabase("QSQLITE", "1");
    db.setDatabaseName(home.absolutePath() + "/trainDB");
    dbconn = db.database("1");

    if (!dbconn.isOpen()) {
        QMessageBox::critical(0, qApp->translate("TrainDB","Cannot open database"),
                       qApp->translate("TrainDB","Unable to establish a database connection.\n"
                                       "This feature requires SQLite support. Please read "
                                       "the Qt SQL driver documentation for information how "
                                       "to build it.\n\n"
                                       "Click Cancel to exit."), QMessageBox::Cancel);
    } else {


        createDatabase();
    }
}
