checkComplete(){
    int i,j,k;
    SIDE_COLOR c;
    for (i=0;i<6;i++){
        for (j=0;j<3;j++){
            for (k=0;k<3;k++){
                if (j==0 && k==0){
                    c = (*(faces[i]->pieces[j][k]))->getSideColor(faces[i]->getSide());
                } else if ((*(faces[i]->pieces[j][k]))->getSideColor(faces[i]->getSide()) != c) {
                    return false;
                }
            }
        }
    }
    return true;
}
