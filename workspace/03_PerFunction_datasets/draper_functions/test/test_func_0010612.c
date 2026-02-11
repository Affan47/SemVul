creaArxiuImatge(QString nomArxiu){
if (!nomArxiu.isEmpty()){
    QRectF rectFigura =conjuntMostra->rectangleFigura();
    QImage *image1 = new QImage(rectFigura.width(),
                                rectFigura.height(),
                                QImage::Format_ARGB32_Premultiplied);
    QPainter *painter= new QPainter(image1);
    conjuntMostra->conjuntSolucio();
    sceneMostra->update();
    QRectF target;
    sceneMostra->render(painter,target,rectFigura);
    painter->end();
    QString  nomArxiuImatge;
    nomArxiuImatge=QDir::homePath ()+QDir().separator()+"tangram"+QDir().separator()+nomArxiu+".png";
    QFile arxiu(nomArxiuImatge);
    arxiu.remove(nomArxiuImatge);
    if(!image1->save(nomArxiuImatge)){
        qDebug("no s'ha desat");
    }
  }
}
