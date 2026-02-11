cell_set_volume(cell c){
 int i,j,r,row;

 cly_T=Imatrix_resize(cly_T,1,cly_R);
 cly_U=HMresize(cly_U,cly_Dim,cly_Dim);
 cly_M=HMresize(cly_M,cly_Dim,cly_Dim);

 for(i=1;i<=cly_R;i++)*IVref(cly_T,i)=-1;

 row=1;
 for(i=0;i<=cly_N;i++){
   r=Ipnt_idx(cell_pnt(c,i));
   if (*IVref(cly_T,r)==-1){
             *IVref(cly_T,r)=i;
   }
   else{
    for(j=1;j<=cly_Dim;j++){
      HLMset(cly_M,row,j,cell_point(c,i,j)-cell_point(c,*IVref(cly_T,r),j));
    }
    row++;
   }
 }
 HMdet(cly_M,cly_U,r);
 return (cell_volume(c)=r);
}
