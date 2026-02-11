carregaFiguresResoltes(){
QString nomArxiu=nomArxiuFiguresResoltes();
QDir dirArxiu;
 if (dirArxiu.exists(nomArxiu)){
     QFile arxiu(nomArxiu);
     if (arxiu.open(QFile::ReadOnly | QFile::Text)){
        QTextStream lectura(&arxiu);
        QString linia0 = lectura.readLine();
        while (!linia0.isNull()) {
            figuresResoltesList->append(linia0);
            linia0 = lectura.readLine();
     }
     }
 }
figuresResoltesList->sort();
}
