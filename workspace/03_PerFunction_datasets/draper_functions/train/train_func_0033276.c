borrar_rec(sNodo* nodo){
    if(nodo == NULL){
        return;
    }
    for(unsigned int i=0;i<8;i++){
        borrar_rec(nodo->nodos[i]);
    }
    delete nodo;
}
