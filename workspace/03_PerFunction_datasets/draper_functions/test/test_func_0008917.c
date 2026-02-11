llegeixLiniaArxiu(QString arxiu, int linia){

    QFile arxiuData(arxiu);
    QString linia0;

    if (arxiuData.open(QIODevice::ReadOnly | QIODevice::Text)){
     QTextStream entrada(&arxiuData);
     linia0 = entrada.readLine();
     int numeroLinia=1;
     while ( (!linia0.isNull())
         && (numeroLinia<linia) ) {
         linia0 = entrada.readLine();
         numeroLinia++;
         }
     }
 return linia0;
}
