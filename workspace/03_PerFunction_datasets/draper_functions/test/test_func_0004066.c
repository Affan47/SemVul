pecaEnLimits(){
    QVector<QPointF> vertexPeca;
    puntsVertexPeca(vertexPeca);
    bool enLimits=true;
    for(int j=0;j<=vertexPeca.size()-1;j++){
        if (!scene()->sceneRect().contains(vertexPeca.value(j))){
           enLimits=false;
        }
    }
return enLimits;
}
