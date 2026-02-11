qcode_opnlab( QCode* qcode, char inst, char* label_name ){
    int  numlabel;
    NUMLABEL( numlabel, label_name );
    qcode_oplab( qcode, inst, numlabel );
}
