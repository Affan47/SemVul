rv34_inv_transform_noround(DCTELEM *block){
    int temp[16];
    int i;

    rv34_row_transform(temp, block);

    for(i=0; i<4; i++){
        const int z0= 13*(temp[4*0+i] +    temp[4*2+i]);
        const int z1= 13*(temp[4*0+i] -    temp[4*2+i]);
        const int z2=  7* temp[4*1+i] - 17*temp[4*3+i];
        const int z3= 17* temp[4*1+i] +  7*temp[4*3+i];

        block[i*8+0]= ((z0 + z3)*3)>>11;
        block[i*8+1]= ((z1 + z2)*3)>>11;
        block[i*8+2]= ((z1 - z2)*3)>>11;
        block[i*8+3]= ((z0 - z3)*3)>>11;
    }

}
