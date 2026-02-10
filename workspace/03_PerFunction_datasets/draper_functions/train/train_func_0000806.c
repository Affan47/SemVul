vertexInferiorDreta(){
  QPointF verInferiorDreta(0.0,0.0);
  QVector<QPointF> pSolucio;
  for(int i=0;i<=arrayPeces.size()-1;i++){
     arrayPeces[i]->puntsSolucio(pSolucio,1.0);
     for(int j=0;j<=pSolucio.size()-1;j++){
        verInferiorDreta.setX(qMax(pSolucio[j].x(),
                                   verInferiorDreta.rx()));
        verInferiorDreta.setY(qMax(pSolucio[j].y(),
                                   verInferiorDreta.ry()));
     }
  }
 return verInferiorDreta;
 }
