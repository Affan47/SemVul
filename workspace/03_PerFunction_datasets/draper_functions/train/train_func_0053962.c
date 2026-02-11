generaOrdrePecesGeneracioFiguraAtzar(){
  QList<int> llista;
  while (llista.size()<conjuntFigura->arrayPeces.size()){
      int nombre=generaNombreAtzar(rellotgeAtzar.elapsed());
      if(!llista.contains(nombre % conjuntFigura->arrayPeces.size())){
          llista.append(nombre % conjuntFigura->arrayPeces.size());
      }
  }


return llista;
}
