maximize(WU& wu,box& cube,FXuchar dir,FXint first,FXint last,FXint *cut,FXint whole_r,FXint whole_g,FXint whole_b,FXint whole_w){
  register FXint half_r,half_g,half_b,half_w,base_r,base_g,base_b,base_w,i;
  register FXfloat temp,max;

  base_r=bottom(cube,dir,wu.mr);
  base_g=bottom(cube,dir,wu.mg);
  base_b=bottom(cube,dir,wu.mb);
  base_w=bottom(cube,dir,wu.wt);

  max=0.0f;
  *cut=-1;
  for(i=first; i<last; ++i){

    half_r=base_r+top(cube,dir,i,wu.mr);
    half_g=base_g+top(cube,dir,i,wu.mg);
    half_b=base_b+top(cube,dir,i,wu.mb);
    half_w=base_w+top(cube,dir,i,wu.wt);


    if(half_w==0) continue;

    temp=((FXfloat)half_r*half_r + (FXfloat)half_g*half_g + (FXfloat)half_b*half_b)/half_w;

    half_r=whole_r-half_r;
    half_g=whole_g-half_g;
    half_b=whole_b-half_b;
    half_w=whole_w-half_w;


    if(half_w==0) continue;

    temp += ((FXfloat)half_r*half_r + (FXfloat)half_g*half_g + (FXfloat)half_b*half_b)/half_w;

    if(temp>max){ max=temp; *cut=i; }
    }
  return max;
  }
