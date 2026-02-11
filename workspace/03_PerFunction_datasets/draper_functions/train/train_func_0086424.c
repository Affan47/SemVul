DeleteConfitems(){
    while (CurrentConfitem>0){
        CurrentConfitem--;
        tDESTROY(configuration[CurrentConfitem]);
    }
}
