conjuntVisible(bool visible){
 for(int i=0;i<=arrayPeces.size()-1;i++){
       arrayPeces[i]->pecaVisible=visible;
       arrayPeces[i]->actualitzaPeca();
       }
}
