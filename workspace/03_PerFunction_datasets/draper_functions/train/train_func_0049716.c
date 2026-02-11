figuraJaResoltaPosicioPeces(QString nomFigura){
    if (figuraJaResolta(nomFigura)){
    QString nom=QString("%1;%2;%3").arg(configuracioJoc->tipusTangram).arg(configuracioJoc->nivellJoc).arg(nomFigura);
    QRegExp rx(nom+";*");
    rx.setPatternSyntax(QRegExp::Wildcard);
    QString dadesFigura=figuresResoltesList->value(figuresResoltesList->indexOf(rx));
    QStringList dadesFiguraList=dadesFigura.split(";");
    return dadesFiguraList.value(3);
    }
 return QString("");
}
